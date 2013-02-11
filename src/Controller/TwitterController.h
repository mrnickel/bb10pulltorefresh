/*
 * TwitterController.h
 *
 *  Created on: Feb 11, 2013
 *      Author: ryannickel
 */

#ifndef TWITTERCONTROLLER_H_
#define TWITTERCONTROLLER_H_

#include <QtCore/QObject>
#include <bb/cascades/Container>
#include <bb/cascades/ListView>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Label>
#include <QTimer>
#include "Twitter.h"

class TwitterController : public QObject
{
	Q_OBJECT
public:
	TwitterController(QObject *parent = 0);
	virtual ~TwitterController();

public slots:

    void parseComplete(bool completed, QString title);
    void loadingTweets();
    void refresh();

private:
    bb::cascades::ListView *_tweetList;
    Twitter *model;
    QObject *_activityIndicator;
};

#endif /* TWITTERCONTROLLER_H_ */
