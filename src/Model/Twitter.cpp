/*
 * Twitter.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: ryannickel
 */

#include "Twitter.h"
#include <bb/data/JsonDataAccess>
#include "Tweet.h"

Twitter::Twitter() {
	qmlRegisterType<Tweet>("ryannickel", 1, 0, "Tweet");
	_loading = false;
}

Twitter::~Twitter() {
	// TODO Auto-generated destructor stub
}

void Twitter::requestData()
{
	if (_loading) {
		return;
	}

	_loading = true;
	emit tweetLoadingStart();

    netManager = new QNetworkAccessManager();
    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    if (!netManager)
    {
        //emit complete("Unable to create QNetworkAccessManager!", false);
        return;
    }

    QString queryUri = "http://search.twitter.com/search.json?q=%22BlackBerry10%22";
    qDebug() << queryUri;
    QUrl url(queryUri);
    QNetworkRequest req(url);

    QNetworkReply* ipReply = netManager->get(req);
    connect(ipReply, SIGNAL(finished()), this, SLOT(onDataReceived()));
}

void Twitter::replyFinished(QNetworkReply* reply)
{
	QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

	if (!possibleRedirectUrl.toUrl().isEmpty()) {
	    QNetworkRequest req(possibleRedirectUrl.toUrl());
	    qDebug("Redirected to: ");
	    qDebug() << possibleRedirectUrl.toUrl();
	    QNetworkReply* ipReply = netManager->get(req);
	    connect(ipReply, SIGNAL(finished()), this, SLOT(onDataReceived()));
	}
}

int Twitter::childCount(const QVariantList& indexPath)
{
	//we're working with the first item.
	if (indexPath.isEmpty()) {
		return _tweetList.size();
	}
	return 0;
}

bool Twitter::hasChildren(const QVariantList& indexPath)
{
	return childCount(indexPath) > 0;
}

QVariant Twitter::data(const QVariantList& indexPath)
{
	return _tweetList.at(indexPath[0].toInt());
}

void Twitter::onDataReceived()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString response;
    bool success = false;
    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            int available = reply->bytesAvailable();
            if (available > 0)
            {
                int bufSize = sizeof(char) * available + sizeof(char);
                QByteArray buffer(bufSize, 0);
                reply->read(buffer.data(), available);
                response = QString(buffer);
                success = true;
            }
        }
        else
        {
            response =  QString("Error: ") + reply->errorString() + QString(" status:") + reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
            emit tweetParseComplete(false, "We can't connect to the internet");
        }
        reply->deleteLater();
    }
    if (success )
    {
    	if (response != "[]") {
    		bb::data::JsonDataAccess jda;
    		QVariant jsonva = jda.loadFromBuffer(response);
    		QVariantMap map = jsonva.toMap();
    		QVariantList results = map.value("results").toList();
    		//okay let's get the news items

    		int numTweets = 0;
    		foreach (QVariant v, results) {
    			QVariantMap map = v.toMap();

    			Tweet *tweet = new Tweet();
    			tweet->parse(v);

    			QVariant q = QVariant::fromValue(tweet);

        		_tweetList.append(q); //to go from a QVariant back to a Tweet* item: Tweet *Tweet = q.value<Tweet*>();

    			QVariantList path;
				path.append(_tweetList.indexOf(q));

				emit  itemAdded (path);
				numTweets++;
    		}

        	if (numTweets > 0) {
        		emit tweetParseComplete(true, "Parsed successfully");
        	} else {
        		if (_tweetList.count() == 0) {
        			emit tweetParseComplete(false, "No Tweets yet");
        		}
        	}
    	}

    }
    _loading = false;
}

int Twitter::numRecs()
{
	return _tweetList.count();
}

void Twitter::refreshData()
{
	_tweetList.clear();
	emit itemsChanged(bb::cascades::DataModelChangeType::Init);
	requestData();
}

bool Twitter::loading()
{
	return _loading;
}

