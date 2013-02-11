/*
 * Twitter.h
 *
 *  Created on: Feb 11, 2013
 *      Author: ryannickel
 */

#ifndef TWITTER_H_
#define TWITTER_H_

#include <QtCore/QObject>
#include <QVariant>
#include <bb/cascades/DataModel>
#include <QVector>
#include <bb/cascades/DataModel>
#include <QtNetwork/QNetworkReply>

class Twitter : public bb::cascades::DataModel
{
	Q_OBJECT
public:
	Twitter();
	virtual ~Twitter();

	void requestData();
    virtual int childCount(const QVariantList& indexPath);
    virtual bool hasChildren(const QVariantList& indexPath);
    virtual QVariant data(const QVariantList& indexPath);
    int numRecs();
    void refreshData();
    bool loading();

public slots:
    void onDataReceived();
    void replyFinished(QNetworkReply* reply);

signals:
	void tweetParseComplete(bool success, QString message);
	void tweetLoadingStart();

private:
	bool _loading;
	QVariantList _tweetList;
	QNetworkAccessManager* netManager;
};

#endif /* TWITTER_H_ */
