/*
 * TwitterController.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: ryannickel
 */

#include <bb/cascades/Application>
#include <bb/cascades/AbstractPane>
#include <QVariant>
#include <QObject>
#include <bb/cascades/QmlDocument>
#include "Tweet.h"
#include "TwitterController.h"

using namespace bb::cascades;

TwitterController::TwitterController(QObject *parent)
    : QObject(parent)
{
    QmlDocument* qml = QmlDocument::create("asset:///main.qml").parent(this);

    AbstractPane* root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);

    _tweetList = Application::instance()->scene()->findChild<bb::cascades::ListView*>("tweetList");
    _tweetList->setProperty("loading", true);

	model = new Twitter();

	_tweetList->setDataModel(model);
    connect(model, SIGNAL(tweetParseComplete(bool, QString)), this, SLOT(parseComplete(bool, QString)));
    connect(model, SIGNAL(tweetLoadingStart()), this, SLOT(loadingTweets()));
    connect(_tweetList, SIGNAL(refreshTriggered()), this, SLOT(refresh()));
    model->requestData();
}

TwitterController::~TwitterController() {
	// TODO Auto-generated destructor stub
}

void TwitterController::parseComplete(bool completed, QString title)
{
	//stop showing the loading indicator
	if (!completed) {
		//show toast error
		qDebug() << "Show toast error";
	} else {
		_tweetList->setProperty("loading", false);
	}
}

void TwitterController::loadingTweets()
{
	_tweetList->setProperty("loading", true);
}

void TwitterController::refresh()
{
	if (!model->loading()) {
		model->refreshData();
	}
}
