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

/**
 * @file InstantMessaging.h
 * @author Florin Leu
 * @date 09 Feb 2011
 *
 * @brief PIM Field Instant Messaging class.
 *
 **/

#ifndef __INSTANTMESSAGING_H__
#define __INSTANTMESSAGING_H__

#include <IX_PIM.h>

namespace PIM
{
	class InstantMessaging
	{
		public:
			enum eTypes
			{
				//The constant describes a home IM address.
				HOME,
				//The constant describes a work IM address.
				WORK,
				//The constant describes a different IM address type.
				OTHER,
				//The constant describes a custom IM address type.
				//The field's label can be set.
				CUSTOM
			};

			enum eProtocols
			{
				//This constant describes an AIM protocol.
				PROTOCOL_AIM = 0,
				//This constant describes a MSN protocol.
				PROTOCOL_MSN,
				//This constant describes a Yahoo protocol.
				PROTOCOL_YAHOO,
				//This constant describes a Skype protocol.
				PROTOCOL_SKYPE,
				//This constant describes a QQ protocol.
				PROTOCOL_QQ,
				//This constant describes a Google Talk protocol.
				PROTOCOL_GOOGLETALK,
				//This constant describes an ICQ protocol.
				PROTOCOL_ICQ,
				//This constant describes a Jabber protocol.
				PROTOCOL_JABBER,
				//This constant describes a NetMeeting protocol.
				PROTOCOL_NETMEETING,
				//This constant describes a custom protocol.
				PROTOCOL_CUSTOM
			};

			enum eSubFields
			{
				//The constant describes an IM username.
				USERNAME = 0,
				//The constant describes an IM protocol.
				PROTOCOL
			};

			/**
			 * Constructor.
			 */
			InstantMessaging();

			/**
			 * Destructor.
			 */
			~InstantMessaging();

			/**
			 * Reads a contact's IM.
			 * @param args The arguments needed to read the IM.
			 * @param index The index of the IM to read.
			 */
			void read(MA_PIM_ARGS& args, int index);

			/**
			 * Writes a contact's IM.
			 * @param args The values to write.
			 * @index args The index of the IM to write.
			 */
			void write(MA_PIM_ARGS& args, int index);

			/**
			 * Deletes a contact's IM.
			 * @param handle The handle of the contact.
			 * @param index  The index of the IM to delete.
			 */
			void remove(MAHandle handle, int index);

			/**
			 * Gets the contact's IM username.
			 * @return The username of the contact.
			 */
			const wchar* const getUsername() const;

			/**
			 * Sets the contact's IM username.
			 * @param username The value to set.
			 */
			void setUsername(const wchar* const username);

			/**
			 * Gets the IM protocol.
			 * @return The protocol of the IM.
			 */
			const eProtocols& getProtocol() const;

			/**
			 * Sets the IM protocol.
			 * @param protocol The value to set.
			 */
			void setProtocol(const eProtocols& protocol);

			/**
			 * Gets the IM protocol label.
			 * @return The protocol label of the IM.
			 */
			const wchar* const getProtocolLabel() const;

			/**
			 * Sets the IM protocol label.
			 * @param protocolLabel The value to set.
			 */
			void setProtocolLabel(const wchar* const protocolLabel);

			/**
			 * Gets the IM type.
			 * @return The type of the IM.
			 */
			const eTypes& getType() const;

			/**
			 * Sets the IM type.
			 * @param type The value to set.
			 */
			void setType(const eTypes& type);

			/**
			 * Gets the IM label.
			 * @return The label of the IM.
			 */
			const wchar* const getLabel() const;

			/**
			 * Sets the IM label.
			 * @param state The value to set.
			 */
			void setLabel(const wchar* const label);

			/**
			 * Checks if this is or not a primary IM.
			 * @return True if this is a primary IM.
			 */
			const bool isPrimary() const;

			/**
			 * Sets this as a primary IM.
			 * @param primary true if this is a primary IM.
			 */
			void setPrimary(const bool primary);

		private:
			/**
			 * Reads the protocol of the IM.
			 * @param handle The handle of the contact.
			 * @param index The index of this IM.
			 */
			void readProtocol(const MAAddress buffer);

			/**
			 * Reads the protocol label of the IM.
			 * @param handle The handle of the contact.
			 * @param index The index of this IM.
			 */
			void readProtocolLabel(const MAAddress buffer);

			/**
			 * Reads the type of the IM.
			 * @param handle The handle of the contact.
			 * @param index The index of this IM.
			 */
			void readType(const MAHandle handle, const int index);

			/**
			 * Reads the label of the IM.
			 * @param handle The handle of the contact.
			 * @param index The index of this IM.
			 */
			void readLabel(const MAHandle handle, const int index);

			/**
			 * Gets the protocol string according to mProtocol.
			 * @return The protocol name.
			 */
			wchar* getProtocolName() const;

			/**
			 * Computes the IM attribute.
			 * @return The IM attribute.
			 */
			const int getAttribute() const;

		private:
			//The user name for the instant messaging.
			wchar* mUsername;
			//The protocol of the instant messaging.
			eProtocols mProtocol;
			//The user defined protocol.
			wchar* mProtocolLabel;

			//The type of data.
			eTypes mType;
			//The user defined label.
			wchar* mLabel;
			//Shows if this is a primary instant messaging or not.
			bool mIsPrimary;
	};

} //PIM

#endif //__INSTANTMESSAGING_H__
