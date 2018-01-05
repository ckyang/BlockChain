//
//  dialog.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/29/17.
//

#include <assert.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtGui/QPixmap>
#include <QtGui/QMovie>
#include "dialog.h"
#include "factory.h"
#include "blockchain.h"
#include "talk.h"

dialog::dialog(QWidget *parent, QApplication* app)
:QDialog(parent), m_app(app)
{
    assert(m_app);
    m_mainLayout = new QGridLayout(this);
    m_loadingMovie = new QMovie("/Users/CK-Yang/Qt/image/loading.gif");
//    m_tickPix = new QPixmap("/Users/CK-Yang/Qt/image/tick.png");
//    m_loadingMovie = new QMovie(":/image/loading.gif");
    m_tickPix = new QPixmap(QCoreApplication::applicationDirPath() + "/tick.png");

    m_addBlockLayout = new QHBoxLayout(this);
    m_addBlockButton = new QPushButton("+Block", this);
    m_addBlockNameEdit = new QLineEdit(this);
    m_addBlockLabel = new QLabel("");

    m_addBlockLayout->addWidget(m_addBlockButton);
    m_addBlockLayout->addWidget(m_addBlockNameEdit);
    m_addBlockLayout->addWidget(m_addBlockLabel);
    m_addBlockLayout->setStretchFactor(m_addBlockButton, 1);
    m_addBlockLayout->setStretchFactor(m_addBlockNameEdit, 999);
    m_addBlockLayout->setStretchFactor(m_addBlockLabel, 1);
    connect(m_addBlockButton, SIGNAL(clicked()), this, SLOT(addBlock()));

    m_blockChainListLayout = new QVBoxLayout(this);
    m_blockChainTitleLabel = new QLabel("Current Block Chain");
    m_blockChainListLabel = new QLabel("Empty");
    m_blockChainScrollArea = new QScrollArea;
    m_blockChainScrollArea->setStyleSheet("background-color:lightcyan;");
    m_blockChainScrollArea->setWidget(m_blockChainListLabel);
    m_blockChainListLayout->addWidget(m_blockChainTitleLabel);
    m_blockChainListLayout->addWidget(m_blockChainScrollArea);
    m_blockChainListLayout->setStretch(0, 1);
    m_blockChainListLayout->setStretch(1, 10);
    
    m_logLabel = new QLabel("QT initialized.");
    m_logLabel->setStyleSheet("QLabel { background-color:transparent; color : lime; }");
    m_logScrollArea = new QScrollArea;
    m_logScrollArea->setStyleSheet("background-color:black;");
    m_logScrollArea->resize (5, 5);
    m_logScrollArea->setWidget(m_logLabel);

    m_mainLayout->addLayout(m_addBlockLayout, 0, 0);
    m_mainLayout->addLayout(m_blockChainListLayout, 1, 0);
    m_mainLayout->addWidget(m_logScrollArea, 2, 0);
    m_mainLayout->setRowStretch(0, 1);
    m_mainLayout->setRowStretch(1, 7);
    m_mainLayout->setRowStretch(2, 2);

    m_controller = new dialog_controller();
    m_controller->moveToThread(&workerThread);
    connect(&workerThread, SIGNAL(finished()), m_controller, SLOT(deleteLater()));
    connect(this, SIGNAL(appendLog(QString)), m_controller, SLOT(operateAppendLog(QString)));
    connect(m_controller, SIGNAL(resultReadyAppendLog(QString)), this, SLOT(handleAppendLog(QString)));
    connect(this, SIGNAL(updateBlockChainList()), m_controller, SLOT(operateUpdateBlockChainList()));
    connect(m_controller, SIGNAL(resultReadyUpdateBlockChainList()), this, SLOT(handleUpdateBlockChainList()));
    workerThread.start();
}

dialog::~dialog()
{
    delete(m_mainLayout);
    delete(m_addBlockLayout);
    delete(m_blockChainListLayout);
    delete(m_addBlockButton);
    delete(m_addBlockNameEdit);
    delete(m_addBlockLabel);
    delete(m_blockChainTitleLabel);
    delete(m_blockChainListLabel);
    delete(m_blockChainScrollArea);
    delete(m_logLabel);
    delete(m_logScrollArea);
    delete(m_loadingMovie);
    delete(m_tickPix);
    workerThread.quit();
    workerThread.wait();
    delete(m_controller);
}

void dialog::addBlock()
{
//    m_addBlockLabel->setMovie(m_loadingMovie);
//    m_loadingMovie->start();

    blockChain* blockChainObject = factory::GetBlockChain();
    blockChainObject->addBlock(blockChainObject->generateNextBlock(m_addBlockNameEdit->text().toUtf8().constData()), true);
    m_addBlockNameEdit->clear();
    updateBlockChainList();

    m_addBlockLabel->setPixmap(*m_tickPix);
}

void dialog::handleUpdateBlockChainList()
{
    m_blockChainListLabel->setText(factory::GetBlockChain()->getChainInfo(true).c_str());
    m_blockChainListLabel->adjustSize();
    m_blockChainScrollArea->widget()->resize(m_blockChainScrollArea->widget()->sizeHint());
    m_app->processEvents();
    m_blockChainScrollArea->verticalScrollBar()->setValue(m_blockChainScrollArea->verticalScrollBar()->minimum());
    m_blockChainScrollArea->horizontalScrollBar()->setValue(m_blockChainScrollArea->horizontalScrollBar()->minimum());
}

void dialog::handleAppendLog(const QString& log)
{
    m_logLabel->setText(m_logLabel->text().append("\n").append(log));
    m_logLabel->adjustSize();
    m_logScrollArea->widget()->resize(m_logScrollArea->widget()->sizeHint());
    m_app->processEvents();
    m_logScrollArea->verticalScrollBar()->setValue(m_logScrollArea->verticalScrollBar()->maximum());
    m_logScrollArea->horizontalScrollBar()->setValue(m_logScrollArea->horizontalScrollBar()->minimum());
}

void dialog_controller::operateAppendLog(const QString& log)
{
    emit resultReadyAppendLog(log);
}

void dialog_controller::operateUpdateBlockChainList()
{
    emit resultReadyUpdateBlockChainList();
}
