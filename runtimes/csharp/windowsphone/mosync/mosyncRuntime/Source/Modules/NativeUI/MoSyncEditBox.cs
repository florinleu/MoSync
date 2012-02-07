﻿/* Copyright (C) 2011 MoSync AB

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
/**
 * @file EditBox.cs
 * @author Rata Gabriela
 *         ovidiu
 *
 * @brief This represents the EditBox Widget implementation for the NativeUI
 *        component on Windows Phone 7, language C#
 *
 * @platform WP 7.1
 **/

using Microsoft.Phone.Controls;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Navigation;
using System;
using System.Text.RegularExpressions;
using System.Reflection;
using System.Windows.Media;
using System.Windows.Input;

using System.Globalization;


namespace MoSync
{
    namespace NativeUI
    {
        /**
         * The EditBox class defines the attributes and behavior of a EditBox widget
         */
        public class EditBox : WidgetBaseWindowsPhone
        {
            /**
             * TextBox control (receives user input)
             */
            protected System.Windows.Controls.TextBox mEditBox;

            /**
             * if set to true, indicates that all the text is a watermark/placeholder
             */
            protected bool mIsWatermarkMode;

            /**
             * if true, indicates that this is the first char entered so delete 
             * the watermark/placeholder
             */
            protected bool mFirstChar;

            /**
              * save the "normal" brush when working with the watermark
              */
            protected Brush mForegroundColor;

            /**
             * The watermark/placeholder text
             */
            protected String mPlaceholderText;


            /**
             * Constructor
             */
            public EditBox()
            {
                mEditBox = new System.Windows.Controls.TextBox();
                View = mEditBox;

                mIsWatermarkMode = false;
                mPlaceholderText = "";

                mForegroundColor = mEditBox.Foreground;

                /**
                 * @brief Sent from the Edit box when it gains focus(the user selects the widget).
                 * The virtual keyboard is shown.
                 *        MAW_EVENT_EDIT_BOX_EDITING_DID_BEGIN
                 */
                mEditBox.GotFocus += new RoutedEventHandler(
                    delegate(object from, RoutedEventArgs args)
                    {
                        /**
                          * simulating the placeholder/watermark
                          */
                        // if watermark present and no user char has been entered
                        if (mIsWatermarkMode && mFirstChar)
                        {
                            // move the cursor to the first position
                            mEditBox.Select(0, 0);
                        }

                        /**
                         * post the event to MoSync runtime
                         */
                        Memory eventData = new Memory(8);
                        const int MAWidgetEventData_eventType = 0;
                        const int MAWidgetEventData_widgetHandle = 4;
                        eventData.WriteInt32(MAWidgetEventData_eventType, MoSync.Constants.MAW_EVENT_EDIT_BOX_EDITING_DID_BEGIN);
                        eventData.WriteInt32(MAWidgetEventData_widgetHandle, mHandle);
                        mRuntime.PostCustomEvent(MoSync.Constants.EVENT_TYPE_WIDGET, eventData);
                    }
                ); // end of mEditBox.GotFocus


                /**
                  * @brief Sent from the Edit box when it loses focus.
                  * The virtual keyboard is hidden.
                  *        MAW_EVENT_EDIT_BOX_EDITING_DID_END
                  */
                mEditBox.LostFocus += new RoutedEventHandler(
                    delegate(object from, RoutedEventArgs args)
                    {
                        /**
                         * simulating the placeholder/watermark
                         */
                        if (mIsWatermarkMode)
                        {
                            // if no text has been entered by the user than leave the watermark text
                            if (mEditBox.Text.Equals(""))
                            {
                                Placeholder = mPlaceholderText;
                                mFirstChar = true;
                            }
                        }

                        /**
                         * post the event to MoSync runtime
                         */
                        Memory eventData = new Memory(8);
                        const int MAWidgetEventData_eventType = 0;
                        const int MAWidgetEventData_widgetHandle = 4;
                        eventData.WriteInt32(MAWidgetEventData_eventType, MoSync.Constants.MAW_EVENT_EDIT_BOX_EDITING_DID_END);
                        eventData.WriteInt32(MAWidgetEventData_widgetHandle, mHandle);
                        mRuntime.PostCustomEvent(MoSync.Constants.EVENT_TYPE_WIDGET, eventData);
                    }
                ); // end of mEditBox.LostFocus


                /**
                  * @brief Sent from the Edit box when the text was changed.
                  *        MAW_EVENT_EDIT_BOX_TEXT_CHANGED
                  */
                mFirstChar = true;
                mEditBox.TextInputStart += new TextCompositionEventHandler(
                    delegate(object from, TextCompositionEventArgs args)
                    {
                        /**
                          * simulating the placeholder/watermark
                          */
                        if (mFirstChar)
                        {
                            mFirstChar = false;
                            mEditBox.Text = "";

                            // change the foreground to "normal" for user input
                            mEditBox.Foreground = mForegroundColor;
                        }

                        /**
                         * post the event to MoSync runtime
                         */
                        Memory eventData = new Memory(8);
                        const int MAWidgetEventData_eventType = 0;
                        const int MAWidgetEventData_widgetHandle = 4;
                        eventData.WriteInt32(MAWidgetEventData_eventType, MoSync.Constants.MAW_EVENT_EDIT_BOX_TEXT_CHANGED);
                        eventData.WriteInt32(MAWidgetEventData_widgetHandle, mHandle);
                        mRuntime.PostCustomEvent(MoSync.Constants.EVENT_TYPE_WIDGET, eventData);
                    }
                ); // end of TextInputStart

                /**
                 * @brief Sent from the Edit box when the return button was pressed.
                 * On iphone platform the virtual keyboard is not closed after receiving this event.
                 * EDIT_BOX_RETURN
                 */
                // Not available on Windows Phone 7.1
            }


            /**
             * Property for setting and getting the text that the edit box contains.
             */
            [MoSyncWidgetProperty(MoSync.Constants.MAW_EDIT_BOX_TEXT)]
            public String Text
            {
                set
                {
                    mEditBox.Text = value;
                }
                get
                {
                    return mEditBox.Text;
                }
            }


            /**
            * Property for setting the default text that the edit box will contain when first displayed
            *
            * Since the Watermark is not yet implemented we use the solution suggested by MS 
            * (http://msdn.microsoft.com/en-us/library/system.windows.controls.textbox(v=vs.95).aspx)
            */
            [MoSyncWidgetProperty(MoSync.Constants.MAW_EDIT_BOX_PLACEHOLDER)]
            public String Placeholder
            {
                set
                {
                    mIsWatermarkMode = true;

                    // save the "normal" brush
                    mForegroundColor = mEditBox.Foreground;

                    SolidColorBrush waterMarkBrush = new SolidColorBrush();
                    waterMarkBrush.Color = Colors.Gray;
                    mEditBox.Foreground = waterMarkBrush;
                    mPlaceholderText = value;

                    mEditBox.Text = mPlaceholderText;
                }
            }


            /**
             * Property for showing/hidding the keyboard
             * set: accepts a String containg the values "true" and "false"
             *
             * Windows Phone 7 doesn't have a way to hide the keyboard
             * other than setting focus to another control that doesn't accept input, thus hiding the keyboard;
             **/
            [MoSyncWidgetProperty(MoSync.Constants.MAW_EDIT_BOX_SHOW_KEYBOARD)]
            public String ShowKeyboard
            {
                set
                {
                    if (value.Equals("true"))
                    {
                        mEditBox.Focus();
                    }
                    else if (value.Equals("false"))
                    {
                        // we need to focus another, non-input element in order to hide the keyboard
                        try
                        {
                            // the parent is most probable to exist and be a non-input control
                            System.Windows.Controls.Control ctrl = (System.Windows.Controls.Control)mEditBox.Parent;
                            ctrl.Focus();
                        }
                        catch
                        {
                        }
                    }
                }
            }


            /**
             * Property for setting the input mode for the edit box.
             * The values have to be the constants defined in IX_WIDGET.h (WidgetEditBoxConstants)  MAW_EDIT_BOX_TYPE_ANY,
             * MAW_EDIT_BOX_TYPE_EMAILADDR, MAW_EDIT_BOX_TYPE_EMAILADDR, MAW_EDIT_BOX_TYPE_PHONENUMBER ect.
             */
            [MoSyncWidgetProperty(MoSync.Constants.MAW_EDIT_BOX_INPUT_MODE)]
            public String InputMode
            {
                set
                {
                    int inputType = 0;
                    if (!int.TryParse(value, out inputType))
                    {
                        return;
                    }


                    switch (inputType)
                    {
                        case 0:			    //todo: check if Default this is equivalent option to MAW_EDIT_BOX_TYPE_ANY
                            setInputMode(System.Windows.Input.InputScopeNameValue.Default);
                            break;
                        case 1:             //MAW_EDIT_BOX_TYPE_EMAILADDR
                            setInputMode(System.Windows.Input.InputScopeNameValue.EmailSmtpAddress);
                            break;
                        case 2:             //MAW_EDIT_BOX_TYPE_NUMERIC integer value
                            setInputMode(System.Windows.Input.InputScopeNameValue.Number);
                            break;
                        case 3:             //MAW_EDIT_BOX_TYPE_PHONENUMBER
                            setInputMode(System.Windows.Input.InputScopeNameValue.TelephoneNumber);
                            break;
                        case 4:             //MAW_EDIT_BOX_TYPE_URL
                            setInputMode(System.Windows.Input.InputScopeNameValue.Url);
                            break;
                        case 5:             //MAW_EDIT_BOX_TYPE_DECIMAL real number
                            setInputMode(System.Windows.Input.InputScopeNameValue.Digits);
                            break;
                        case 6:             //MAW_EDIT_BOX_TYPE_SINGLE_LINE any text except for line breaks
                            mEditBox.TextWrapping = TextWrapping.NoWrap;
                            break;
                    }
                }
            }

            /**
             * Implementation of the InputFlag property
             * Sets the editing flags applied to the edit box.             *
             * valid values: MAW_EDIT_BOX_FLAG_PASSWORD,
             * MAW_EDIT_BOX_FLAG_SENSITIVE, MAW_EDIT_BOX_FLAG_INITIAL_CAPS_ALL_CHARACTERS,
             * MAW_EDIT_BOX_FLAG_INITIAL_CAPS_WORD, MAW_EDIT_BOX_FLAG_INITIAL_CAPS_SENTENCE
             */
            [MoSyncWidgetProperty(MoSync.Constants.MAW_EDIT_BOX_INPUT_FLAG)]
            public String InputFlag
            {
                set
                {
                    int inputFlag = 0;

                    if (!int.TryParse(value, out inputFlag))
                    {
                        return;
                    }

                    switch (inputFlag)
                    {
                        case 0:			    //MAW_EDIT_BOX_FLAG_PASSWORD
                            setInputMode(System.Windows.Input.InputScopeNameValue.Password);
                            break;
                        case 1:             //MAW_EDIT_BOX_FLAG_SENSITIVE
                            setInputMode(System.Windows.Input.InputScopeNameValue.Default);
                            break;
                        case 2:             //MAW_EDIT_BOX_FLAG_INITIAL_CAPS_WORD
                            setInputMode(System.Windows.Input.InputScopeNameValue.PersonalFullName);
                            break;
                        case 3:             //MAW_EDIT_BOX_FLAG_INITIAL_CAPS_SENTENCE
                            setInputMode(System.Windows.Input.InputScopeNameValue.PersonalNamePrefix);
                            break;
                        case 4:             //MAW_EDIT_BOX_FLAG_INITIAL_CAPS_ALL_CHARACTERS
                            setInputMode(System.Windows.Input.InputScopeNameValue.PersonalFullName);
                            break;
                    }
                }
            }


            //MAW_EDIT_BOX_FONT_COLOR property implementation
            [MoSyncWidgetProperty(MoSync.Constants.MAW_EDIT_BOX_FONT_COLOR)]
            public String FontColor
            {
                set
                {
                    System.Windows.Media.SolidColorBrush brush;
                    MoSync.Util.convertStringToColor(value, out brush);
                    mForegroundColor = brush;

                    mEditBox.Foreground = mForegroundColor;
                }
            }


            /**
             * Helper function that sets the input mode of the edit box
             * @param scopeValue: indicates the type of input that is expected from the user.
             * Can have values like: Url, FullFilePath, FileName, EmailUserName, PostalCode, Password, Numeric
             */
            protected void setInputMode(System.Windows.Input.InputScopeNameValue scopeValue)
            {
                try
                {
                    mEditBox.InputScope = new InputScope()
                    {
                        Names = { new InputScopeName() { NameValue = scopeValue } }
                    };
                }
                catch (NotImplementedException)
                {
                    //TODO: return an error value
                }

            }

        } // class EditBox
    } // namespace NativeUI
} // namespace MoSync