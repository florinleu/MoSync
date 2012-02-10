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

namespace PIM
{

	enum eInstantMessagingTypes
	{
		//The constant describes a home IM address.
		INSTANTMESSAGING_HOME,
		//The constant describes a work IM address.
		INSTANTMESSAGING_WORK,
		//The constant describes a different IM address type.
		INSTANTMESSAGING_OTHER,
		//The constant describes a custom IM address type.
		//The field's label can be set.
		INSTANTMESSAGING_CUSTOM
	};

	enum eInstantMessagingProtocols
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
		PROTOCOL_GOOGLE_TALK,
		//This constant describes an ICQ protocol.
		PROTOCOL_ICQ,
		//This constant describes a Jabber protocol.
		PROTOCOL_JABBER,
		//This constant describes a NetMeeting protocol.
		PROTOCOL_NETMEETING,
		//This constant describes a custom protocol.
		PROTOCOL_CUSTOM
	};

	class InstantMessaging
	{
		private:
			//The user name for the instant messaging.
			wchar* mUsername;
			//The protocol of the instant messaging.
			eInstantMessagingProtocols mProtocol;
			//The user defined protocol.
			wchar* mProtocoLabel;

			//The type of data.
			eInstantMessagingTypes mType;
			//The user defined label
			wchar* mLabel;
	};

} //PIM

#endif //__INSTANTMESSAGING_H__
