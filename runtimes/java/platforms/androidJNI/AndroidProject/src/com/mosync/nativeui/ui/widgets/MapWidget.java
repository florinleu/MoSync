/* Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
 */

package com.mosync.nativeui.ui.widgets;

import android.app.Activity;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.mosync.internal.generated.IX_WIDGET;
import com.mosync.nativeui.util.properties.BooleanConverter;
import com.mosync.nativeui.util.properties.IntConverter;
import com.mosync.nativeui.util.properties.InvalidPropertyValueException;
import com.mosync.nativeui.util.properties.PropertyConversionException;

/**
 * Wraps the behavior of a map widget.
 * @author Florin Leu
 */
public class MapWidget extends Widget {

	Activity mActivity;

	private int centerZoomLevel = 0;
	private int centerLatitude = 0;
	private int centerLongitude = 0;
	private int upperLeftLatitude = 0;
	private int upperLeftLongitude = 0;
	private int lowerRightLatitude = 0;
	private int lowerRightLongitude = 0;

	public MapWidget(int handle, Activity activity) {
		super(handle, null);
		mActivity = activity;
	}

	/**
	 * @see Widget.setProperty.
	 */
	@Override
	public boolean setProperty(String property, String value)
			throws PropertyConversionException, InvalidPropertyValueException {

		MapView mapView = (MapView) getView();

		if (property.equals(IX_WIDGET.MAW_MAP_API_KEY_GOOGLE)) {
			MapView map = new MapView(mActivity, value);
			setView(map);
		} else if (mapView == null) {
			return false;
		}

		MapController mapController = mapView.getController();

		if (property.equals(IX_WIDGET.MAW_MAP_TYPE)) {
			mapView.setSatellite(IntConverter.convert(value) == IX_WIDGET.MAW_MAP_TYPE_SATELLITE);
		} else if (property.equals(IX_WIDGET.MAW_MAP_ZOOM_LEVEL)) {
			mapController.setZoom(IntConverter.convert(value));
		} else if (property.equals(IX_WIDGET.MAW_MAP_INTERRACTION_ENABLED)) {
			mapView.setClickable(BooleanConverter.convert(value));
		} else if (property.equals(IX_WIDGET.MAW_MAP_CENTER_LATITUDE)) {
			centerLatitude = IntConverter.convert(value);
		} else if (property.equals(IX_WIDGET.MAW_MAP_CENTER_LONGITUDE)) {
			centerLongitude = IntConverter.convert(value);
		} else if (property.equals(IX_WIDGET.MAW_MAP_CENTER_ZOOM_LEVEL)) {
			centerZoomLevel = IntConverter.convert(value);
		} else if (property.equals(IX_WIDGET.MAW_MAP_CENTERED)) {
			mapController.animateTo(new GeoPoint(centerLatitude,
					centerLongitude));
			mapController.setZoom(centerZoomLevel); // fleu TODO try to animate
													// this too:
													// http://stackoverflow.com/questions/4398412/smooth-zoom-in-mapview
		} else if (property
				.equals(IX_WIDGET.MAW_MAP_VISIBLE_AREA_UPPER_LEFT_CORNER_LATITUDE)) {
			upperLeftLatitude = IntConverter.convert(value);
		} else if (property
				.equals(IX_WIDGET.MAW_MAP_VISIBLE_AREA_UPPER_LEFT_CORNER_LONGITUDE)) {
			upperLeftLongitude = IntConverter.convert(value);
		} else if (property
				.equals(IX_WIDGET.MAW_MAP_VISIBLE_AREA_LOWER_RIGHT_CORNER_LATITUDE)) {
			lowerRightLatitude = IntConverter.convert(value);
		} else if (property
				.equals(IX_WIDGET.MAW_MAP_VISIBLE_AREA_LOWER_RIGHT_CORNER_LONGITUDE)) {
			lowerRightLongitude = IntConverter.convert(value);
		} else if (property.equals(IX_WIDGET.MAW_MAP_CENTERED_ON_VISIBLE_AREA)) {
			// fleu TODO move the map to the view
		} else {
			return super.setProperty(property, value);
		}
		return true;
	}
	// MapView map = new MapView(mActivity, apiKey);
	// super(handle, map);
}
