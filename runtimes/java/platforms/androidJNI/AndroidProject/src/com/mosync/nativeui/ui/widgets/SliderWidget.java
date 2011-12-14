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

import android.widget.SeekBar;

import com.mosync.internal.generated.IX_WIDGET;
import com.mosync.nativeui.util.properties.IntConverter;
import com.mosync.nativeui.util.properties.InvalidPropertyValueException;
import com.mosync.nativeui.util.properties.PropertyConversionException;

/**
 * A slider is an extension of ProgressBar that adds a draggable thumb.
 *
 * @author emma
 */
public class SliderWidget extends Widget
{
	/**
	 * Constructor.
	 *
	 * @param handle Integer handle corresponding to this instance.
	 * @param progressbar A slider wrapped by this widget.
	 */
	public SliderWidget(int handle, SeekBar slider)
	{
		super( handle, slider );
	}

	/**
	 * @see Widget.setProperty.
	 */
	@Override
	public boolean setProperty(String property, String value)
			throws PropertyConversionException, InvalidPropertyValueException
	{
		if( super.setProperty(property, value) )
		{
			return true;
		}

		SeekBar slider = (SeekBar) getView( );

		if( property.equals( IX_WIDGET.MAW_SLIDER_MAX ) )
		{
			slider.setMax(IntConverter.convert( value ));
		}
		else if( property.equals( IX_WIDGET.MAW_SLIDER_VALUE ))
		{
			if ( IntConverter.convert(value) < 0 )
			{
				throw new InvalidPropertyValueException(property, value);
			}

			slider.setProgress(IntConverter.convert( value ));
		}
		else if( property.equals( IX_WIDGET.MAW_SLIDER_INCREASE_VALUE ))
		{
			if ( IntConverter.convert(value) < 0 )
			{
				throw new InvalidPropertyValueException(property, value);
			}

			slider.incrementProgressBy(IntConverter.convert( value ));
		}
		else if( property.equals( IX_WIDGET.MAW_SLIDER_DECREASE_VALUE ))
		{
			if ( IntConverter.convert(value) < 0 )
			{
				throw new InvalidPropertyValueException(property, value);
			}
			int diff = slider.getProgress() - IntConverter.convert(value);
			slider.setProgress(diff);
		}
		else
		{
			return false;
		}
		return true;
	}

	/**
	 * @see Widget.getProperty.
	 */
	@Override
	public String getProperty(String property)
	{
		SeekBar slider = (SeekBar) getView( );

		if( property.equals( IX_WIDGET.MAW_SLIDER_MAX ) )
		{
			return Integer.toString( slider.getMax() );
		}
		else if( property.equals( IX_WIDGET.MAW_SLIDER_VALUE ) )
		{
			return Integer.toString( slider.getProgress() );
		}
		else
		{
			return super.getProperty( property );
		}
	}
}
