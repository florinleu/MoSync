/* Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

package com.mosync.nativeui.ui.custom;

import static com.mosync.internal.generated.MAAPI_consts.EVENT_TYPE_IMAGE_PICKER;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.res.TypedArray;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.Uri;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.ImageView.ScaleType;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.mosync.internal.android.MoSyncThread;
import com.mosync.internal.android.MoSyncThread.ImageCache;
import com.mosync.java.android.R;
import com.mosync.nativeui.util.properties.ColorConverter;


/*
 *  Helpers for the maOpenImageBrowser syscall.
 *  @author emma tresanszki
 */
public class MoSyncImagePicker
{
	// Events for when the Ok or Cancel button are hit.
	final int PICKER_CANCELED = 0;
	final int PICKER_READY = 1;

	final int ROTATE_CLOCKWISE = 90;
	final int ROTATE_COUNTERCLOCKWISE = -90;

	//-------------------------- IMPLEMENTATION --------------------------//

	/**
	 * Constructor.
	 * @param thread The MoSync thread.
	 */
	public MoSyncImagePicker(MoSyncThread thread,Hashtable<Integer, ImageCache> imageTable)
	{
		mMoSyncThread = thread;
		mImageTable = imageTable;
		mPaths = new ArrayList<String>();
		mNames = new ArrayList<String>();
		mBitmapCache = new ArrayList<Bitmap>();
		mRotateSequence = new ArrayList<Integer>();
		// Set the decoder options for the bitmaps.
		// Decode to a smaller image to save memory and run faster.
		// Powers of 2 are often faster/easier for the decoder to honor.
        mDecodingOptions.inSampleSize = 4;
	}

	/*
	 * Open a custom dialog with a gallery view and preview
	 * for the selected item.
	 */
	public void loadGallery()
	{
		mDecodingOptions.inSampleSize = 4;

		// Initialize the selected image handle.
		mImageHandle = -1;
		// Initialize the current position inside the gallery.
		mPosition = -1;

		// Reset the bitmap cache.
		mBitmapCache.clear();

		AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
		builder.setCancelable(true);
		builder.setTitle("Image Picker");

		if ( getImagesUsingCursor() )
		{
	        // Use the screen size at scaling the gallery and preview image.
	        int screenExtent = mMoSyncThread.maGetScrSize();
	        mScrWidth = screenExtent >> 16;
	        mScrHeight = screenExtent & 0xffff;

			// Provide a linear layout with a gallery and a preview of the
			// selected item.
			LinearLayout layout = new LinearLayout(getActivity());
			layout.setOrientation(LinearLayout.VERTICAL);
			layout.setVerticalGravity(Gravity.CENTER);
			layout.setHorizontalGravity(Gravity.CENTER);
			layout.setLayoutParams(new LinearLayout.LayoutParams(
			        LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

			Gallery gallery = new Gallery(getActivity());
			gallery.setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT,
					LayoutParams.FILL_PARENT));
			// Do not call onItemSelected during fling to be faster.
			gallery.setCallbackDuringFling(false);

			// Fill the gallery view with images.
			gallery.setAdapter(new CustomAdapter(getActivity()));
			layout.addView(gallery);

			mPreview = new ImageView(getActivity());
			// Set fixed size, otherwise the widget will resize itself each time an item is selected.
			mPreview.setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT, mScrHeight/2) );
			mPreview.setMinimumWidth(mScrWidth/2);

			// Show preview of the first image.
			Bitmap bitmap = BitmapFactory.decodeFile(mPaths.get(0), mDecodingOptions);
			mPreviewBitmap = bitmap;
			mPreview.setImageBitmap(bitmap);
			scalePreview(mPreview, mPreviewBitmap);
			layout.addView(mPreview);

			// Layout with rotate options in the corners.
			RelativeLayout buttonsLayout = new RelativeLayout(getActivity());
			buttonsLayout.setVerticalGravity(Gravity.TOP);
			buttonsLayout.setLayoutParams(new RelativeLayout.LayoutParams(
			        LayoutParams.FILL_PARENT, mScrHeight/6));

			mRotateCounterclockwise = new Button(getActivity());
			mRotateCounterclockwise.setText("Rotate left");
			RelativeLayout.LayoutParams leftParams = new RelativeLayout.LayoutParams(
					RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT );
			leftParams.addRule( RelativeLayout.ALIGN_PARENT_LEFT );
			mRotateCounterclockwise.setLayoutParams( leftParams );
			mRotateCounterclockwise.setTextColor(ColorConverter.convert("0xFFFFFF"));
			mRotateCounterclockwise.setOnClickListener(new OnClickListener() {

				@Override
				public void onClick(View v) {
					// Save sequence.
					mRotateSequence.add(ROTATE_COUNTERCLOCKWISE);
					// Rotate left and store the current preview bitmap.
					mPreviewBitmap = getRotatedBitmap(mPreviewBitmap, ROTATE_COUNTERCLOCKWISE);
					// Update UI.
		            mPreview.setImageBitmap(mPreviewBitmap);
				}
			});

			mRotateClockwise = new Button(getActivity());
			mRotateClockwise.setText("Rotate right");
			RelativeLayout.LayoutParams rightParams = new RelativeLayout.LayoutParams(
					RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT );
			rightParams.addRule( RelativeLayout.ALIGN_PARENT_RIGHT );
			mRotateClockwise.setLayoutParams( rightParams );
			mRotateClockwise.setTextColor(ColorConverter.convert("0xFFFFFF"));
			mRotateClockwise.setOnClickListener(new OnClickListener() {

				@Override
				public void onClick(View v) {
					// Save sequence.
					mRotateSequence.add(ROTATE_CLOCKWISE);
					// Rotate right and store the current preview bitmap.
					mPreviewBitmap = getRotatedBitmap(mPreviewBitmap, ROTATE_CLOCKWISE);
					// Update UI.
					mPreview.setImageBitmap(mPreviewBitmap);
				}
			});

			buttonsLayout.addView(mRotateCounterclockwise);
			buttonsLayout.addView(mRotateClockwise);
			layout.addView(buttonsLayout);

			gallery.setOnItemSelectedListener(new OnItemSelectedListener() {

				@Override
                public void onItemSelected(AdapterView<?> arg0, View arg1,
                        int pos, long id)
                {
					// Do not show the names, because they could be shown with delay,
					// even after the dialog is closed.
//					Toast.makeText(getActivity(), mNames.get(pos), Toast.LENGTH_SHORT).show();

					// Do not save rotate sequence among selections.
					mRotateSequence.clear();

					// Set the current preview bitmap: bitmap stored by the Adapter.
					mPreviewBitmap = mBitmapCache.get(pos);
					scalePreview(mPreview, mPreviewBitmap);

					// Refresh the preview image.
					// Get the bitmap stored by the Adapter.
		            mPreview.setImageBitmap(mPreviewBitmap);

		            // Save the position of the last selected images.
		            mPosition = pos;
                }

				@Override
                public void onNothingSelected(AdapterView<?> arg0)
                {
                }

			});
			builder.setView(layout);
		}
		else
		{
			builder.setMessage("No images were found on the device!");
		}

		builder.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which)
			{
				if ( !mPaths.isEmpty() )
				{
					// Display only the name of the selected image.
					Toast.makeText(getActivity(), mNames.get(mPosition), Toast.LENGTH_SHORT).show();

					// Save the handle of the selected item and post event.
					mImageHandle = getSelectedImageHandle(mPreviewBitmap);
					// Clear the bitmap cache before closing the dialog.
					mBitmapCache.clear();
					postImagePickerEvent(PICKER_READY);
				}
				else
				{
					postImagePickerEvent(PICKER_CANCELED);
				}
			}
		});
		builder.setNegativeButton("Cancel",
		        new DialogInterface.OnClickListener() {

			        @Override
			        public void onClick(DialogInterface dialog, int which)
			        {
						// Clear the bitmap cache before closing the dialog.
						mBitmapCache.clear();
				        postImagePickerEvent(PICKER_CANCELED);
			        }
		        });
		AlertDialog alertDialog = builder.create();

		// Display the dialog until user provides a selection, or cancels the
		// request.
		alertDialog.show();
	}

	/**
	 * Scale the bitmap to fit the preview view.
	 * @param preview The preview Image widget.
	 * @param bitmap The bitmap content for the preview.
	 */
	private void scalePreview(ImageView preview, Bitmap bitmap)
	{
		if ( bitmap.getWidth() > preview.getLayoutParams().width
				&&
			bitmap.getHeight() > preview.getLayoutParams().height )
        {
			// Scale it to fit.
			preview.setScaleType(ScaleType.FIT_CENTER);
        }
        else
        {
			// If image is smaller that the layout params of this imageview,
			// scale center.
			preview.setScaleType(ScaleType.CENTER_INSIDE);
        }
	}

	/**
	 * Post a message to the MoSync event queue.
	 * The state is: Ready or Canceled.
	 */
	private void postImagePickerEvent(int state)
	{
		int[] event = new int[3];
		event[0] = EVENT_TYPE_IMAGE_PICKER;
		event[1] = state;
		// If Cancel is clicked, the handle is -1.
		event[2] = mImageHandle;

		mMoSyncThread.postEvent(event);
	}

	/*
	 * Parse cursor and select only image paths and names.
	 * Copy them locally.
	 */
	private void parseCursor(Cursor aCursor)
	{
	    if (aCursor != null)
	    {

			if (aCursor.moveToFirst())
			{
		        String filePath;
		        String title;
		        int pathColumn = aCursor.getColumnIndex(
		            MediaStore.Images.Media.DATA);

		        int titleColumn = aCursor.getColumnIndex(
		            MediaStore.Images.Media.TITLE);

		        do {
		            // Get the field values
		            filePath = aCursor.getString(pathColumn);
		            title = aCursor.getString(titleColumn);

		            if ( filePath.toLowerCase().endsWith(".jpg")
							||
						filePath.toLowerCase().endsWith(".png")
							||
						filePath.toLowerCase().endsWith(".jpeg") )
					{
						mPaths.add(filePath);
						mNames.add(title);
		            }

		            // This is for test only.
//					Toast.makeText(getActivity(),"path= "+ filePath+" title="+title ,
//					        Toast.LENGTH_SHORT).show();

		        } while (aCursor.moveToNext());
		    }
	    }
	}

	private boolean getImagesUsingCursor()
	{
		mPaths.clear();
		mNames.clear();

		// Search for both internal and external images.
		Uri externalImages = MediaStore.Images.Media.EXTERNAL_CONTENT_URI;
		Uri internalImages = MediaStore.Images.Media.INTERNAL_CONTENT_URI;

		// Which image properties are we querying.
		String[] projection = new String[]{
			MediaStore.Images.Media._ID,
			// Get the absolute path.
	        MediaStore.Images.Media.DATA,
	        // Get the title for display.
	        MediaStore.Images.Media.TITLE
	};

	    // Make the queries.
	    Cursor internalCursor = getActivity().getContentResolver().query(internalImages,
	            projection, // Which columns to return
	            "",         // Which rows to return (all rows)
	            null,       // Selection arguments (none)
	            ""          // Ordering
	            );

	    parseCursor(internalCursor);

	    Cursor externalCursor = getActivity().getContentResolver().query(externalImages,
	            projection, // Which columns to return
	            "",         // Which rows to return (all rows)
	            null,       // Selection arguments (none)
	            ""          // Ordering
	            );

	    parseCursor(externalCursor);

	    if ( !mPaths.isEmpty() )
	    {
			return true;
	    }
	    else
	    {
			Log.i("MoSync","maImagePickerOpen - no images!!!");
			return false;
	    }
	}

	/**
	 * @return The Activity object.
	 */
	private Activity getActivity()
	{
		return mMoSyncThread.getActivity();
	}

	/**
	 * Rotate a bitmap.
	 * @param originalBitmap The original bitmap.
	 * @param degrees The rotation.
	 * @return the resulting bitmap.
	 */
	private Bitmap getRotatedBitmap(Bitmap originalBitmap, int degrees)
	{
        Matrix matrix = new Matrix();
        matrix.postRotate(degrees);
        Bitmap rotatedBitmap = null;
        try{
			rotatedBitmap = Bitmap.createBitmap(
					originalBitmap, 0, 0, originalBitmap.getWidth(), originalBitmap.getHeight(), matrix, true);
        }catch ( IllegalArgumentException iae)
        {
			Log.i("@@MoSync","maImagePickerOpen Cannot rotate bitmap");
        }

        return rotatedBitmap;
	}

    /**
     * Get the handle of the selected item.
     * Further, post it in a EVENT_TYPE_IMAGE_PICKER event.
     * @return The new handle.
     */
    private int getSelectedImageHandle(Bitmap scaledBitmap)
    {
        // Create handle.
        int dataHandle = mMoSyncThread.nativeCreatePlaceholder();

		// The bitmap was decoded using sample size 4.
        int originalSizeW = scaledBitmap.getWidth()*4;
        int originalSizeH = scaledBitmap.getHeight()*4;

        if ( originalSizeW > mScrWidth * 4
				||
			originalSizeH > mScrHeight *4)
        {
			mImageTable.put(dataHandle, new ImageCache(null, scaledBitmap));

            return dataHandle;
        }
        else if ( originalSizeW > mScrWidth  *2
					||
				originalSizeH > mScrHeight * 2 )
        {
            // If the image is nearly twice as big as the screen, scale to factor 2.
			mDecodingOptions.inSampleSize = 2;
        }
        else
        {
            // If the image is close the the screen, do not subsample it.
			mDecodingOptions.inSampleSize = 1;
        }

        /**
         * If the bitmap needs decoding again compute the same rotating
         * sequence as the user did.
         */
        Bitmap newBitmap = BitmapFactory.decodeFile(mPaths.get(mPosition), mDecodingOptions);
        if ( !mRotateSequence.isEmpty() )
        {
			for (int i=0; i < mRotateSequence.size(); i++)
			{
				newBitmap = getRotatedBitmap(newBitmap, mRotateSequence.get(i));
			}
        }

		if (null == newBitmap)
		{
			Log.i("@@MoSync","maImagePickerOpen Cannot create handle");
			return -1;
//			maPanic(1, "maImagePickerOpen: Unable to create handle");
		}

		mImageTable.put(dataHandle, new ImageCache(null, newBitmap));

        return dataHandle;
    }

    /**
     * Custom adapter for the gallery view list.
     * @author emma
     *
     */
    public class CustomAdapter extends BaseAdapter
    {
        int mGalleryItemBackg;
        private Context mContext;

        public CustomAdapter(Context c)
        {
            mContext = c;
            TypedArray typArray = getActivity().obtainStyledAttributes(R.styleable.GalleryTheme);

            // Set the theme with a frame surrounding gallery items.
            mGalleryItemBackg = typArray.getResourceId(R.styleable.GalleryTheme_android_galleryItemBackground, 0);
            typArray.recycle();
        }

        public int getCount()
        {
			return mPaths.size();
        }

        public Object getItem(int position)
        {
            return position;
        }

        public long getItemId(int position)
        {
            return position;
        }

        public View getView(int position, View convertView, ViewGroup parent)
        {
            ImageView imgView = new ImageView(mContext);
            // Scale the gallery images to be smaller that the preview.
            // Make them square.
            imgView.setLayoutParams(new Gallery.LayoutParams(mScrWidth/3, mScrWidth/3));

            // Check if the bitmap is already in cache.
            if ( mBitmapCache.size() <= position )
            {
				mBitmapCache.add( BitmapFactory.decodeFile(mPaths.get(position), mDecodingOptions) );
            }
            // DO not scale the image if it smaller than the layout params.
			if ( mBitmapCache.get(position).getWidth() > imgView.getLayoutParams().width
					&&
				mBitmapCache.get(position).getHeight() > imgView.getLayoutParams().height )
            {
				// Scale it to fit.
				imgView.setScaleType(ScaleType.FIT_XY);
            }
            else
            {
				// If image is smaller that the layout params of this image view,
				// scale the image uniformly.
				imgView.setScaleType(ScaleType.CENTER_INSIDE);
            }

            imgView.setImageBitmap(mBitmapCache.get(position));
            imgView.setBackgroundResource(mGalleryItemBackg);

            return imgView;
        }
    }

    //--------------------------   Members   --------------------------//

	/**
	 * The MoSync thread object.
	 */
    private MoSyncThread mMoSyncThread;

    /**
     * It has access to the image resource table.
     */
    private Hashtable<Integer, ImageCache> mImageTable;

    /**
     * List of absolute paths to all images on the device.
     */
	private List<String> mPaths;

	/**
	 * List of image names.
	 */
	private List<String> mNames;

	/**
	 * Cache for bitmaps.
	 */
	private List<Bitmap> mBitmapCache;

	/**
	 * The handle of the selected image.
	 */
	private int mImageHandle = -1;

	/**
	 * The current image index.
	 */
	private int mPosition = -1;

	private int mScrWidth = 0;
	private int mScrHeight = 0;

	/**
	 * Decoding options used for bitmaps.
	 */
	BitmapFactory.Options mDecodingOptions = new BitmapFactory.Options() ;

	/**
	 * The preview image.
	 */
	private ImageView mPreview = null;

	/**
	 * The current bitmap in the preview view. Can be rotated.
	 */
	private Bitmap mPreviewBitmap = null;

	/**
	 * The rotate buttons.
	 */
	private Button mRotateClockwise = null;
	private Button mRotateCounterclockwise = null;

	/**
	 * Save the sequence in which the preview is rotated.
	 * If the user selects another item the rotation is not saved.
	 * When user presses OK the sequence needs to be taken into
	 * account because if the photo needs to be decoded again,
	 * it will also be rotated.
	 */
	private List<Integer> mRotateSequence;
}