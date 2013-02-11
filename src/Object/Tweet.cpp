/*
 * Tweet.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: ryannickel
 */

#include "Tweet.h"
#include <QVariant>
#include <QDebug>

Tweet::Tweet()
{
	_type = "tweet";
}

Tweet::~Tweet()
{
	// TODO Auto-generated destructor stub
}

void Tweet::parse(QVariant &item)
{
	QVariantMap map = item.toMap();
	this->_idStr = map.value("id_str").toString();
	this->_fromUser = map.value("from_user").toString();
	this->_fromUserName = map.value("from_user_name").toString();
	this->_idStr = map.value("id_str").toString();
	this->_profileImageURL = map.value("profile_image_url").toString();
	this->_text = map.value("text").toString();
	this->_createdAt = map.value("created_at").toString();
}


QString Tweet::fromUser() const
{
	return _fromUser;
}
QString Tweet::fromUserName() const
{
	return _fromUserName;
}
QString Tweet::idStr() const
{
	return _idStr;
}
QString Tweet::profileImageURL() const
{
	return _profileImageURL;
}
QString Tweet::text() const
{
	return _text;
}
QString Tweet::createdAt() const
{
	return _createdAt;
}
QString Tweet::type() const
{
	return _type;
}
