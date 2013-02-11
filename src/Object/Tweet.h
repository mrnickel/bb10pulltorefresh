/*
 * Tweet.h
 *
 *  Created on: Feb 11, 2012
 *      Author: ryannickel
 */

#ifndef TWEET_H_
#define TWEET_H_

#include <QVariant>
#include <QObject>

class Tweet : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString fromUser READ fromUser NOTIFY tweetUpdated)
	Q_PROPERTY(QString fromUserName READ fromUserName NOTIFY tweetUpdated)
	Q_PROPERTY(QString idStr READ idStr NOTIFY tweetUpdated)
	Q_PROPERTY(QString profileImageURL READ profileImageURL NOTIFY tweetUpdated)
	Q_PROPERTY(QString text READ text NOTIFY tweetUpdated)
	Q_PROPERTY(QString createdAt READ createdAt NOTIFY tweetUpdated)
	Q_PROPERTY(QString type READ type NOTIFY tweetUpdated)

public:
	Tweet();
	virtual ~Tweet();

	void parse(QVariant &item);

	QString fromUser() const;
	QString fromUserName() const;
	QString idStr() const;
	QString profileImageURL() const;
	QString text() const;
	QString createdAt() const;
	QString type() const;

Q_SIGNALS:
	void tweetUpdated();

private:
	QString _fromUser;
	QString _fromUserName;
	QString _idStr;
	QString _profileImageURL;
	QString _text;
	QString _createdAt;
	QString _type;
};
Q_DECLARE_METATYPE( Tweet *);
#endif /* TWEET_H_ */
