//
//  dialog.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/29/17.
//

#include <iostream>
#include <assert.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "dialog.h"
#include "factory.h"
#include "blockchain.h"
#include "talk.h"

dialog::dialog(QWidget *parent, QApplication* app)
:QDialog(parent), m_app(app)
{
    assert(m_app);
    m_mainLayout = new QGridLayout(this);

    m_addBlockLayout = new QHBoxLayout(this);
    m_addBlockButton = new QPushButton("Add", this);
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

    controller *worker = new controller();
    worker->moveToThread(&workerThread);
    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(appendLog(QString)), worker, SLOT(operate(QString)));
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
    workerThread.quit();
    workerThread.wait();
}

void dialog::addBlock()
{
    m_addBlockLabel->setText("Verifying..............");

    blockChain* blockChainObject = factory::GetBlockChain();
    blockChainObject->addBlock(blockChainObject->generateNextBlock(m_addBlockNameEdit->text().toUtf8().constData()), true);
    m_addBlockNameEdit->clear();
    updateBlockChainList();

    m_addBlockLabel->setText("OK!");
}

void dialog::updateBlockChainList()
{
    m_blockChainListLabel->setText(factory::GetBlockChain()->getChainInfo(true).c_str());
    m_blockChainListLabel->adjustSize();
    m_blockChainScrollArea->widget()->resize(m_blockChainScrollArea->widget()->sizeHint());
    m_app->processEvents();
    m_blockChainScrollArea->verticalScrollBar()->setValue(m_blockChainScrollArea->verticalScrollBar()->maximum());
}

void controller::operate(const QString& log)
{
    //TBD
//    cout << log.toStdString() << endl;

    factory::GetDialog()->m_logLabel->setText(factory::GetDialog()->m_logLabel->text().append("\n").append(log));
//    factory::GetDialog()->m_logLabel->adjustSize();
//    factory::GetDialog()->m_logScrollArea->widget()->resize(factory::GetDialog()->m_logScrollArea->widget()->sizeHint());
//    factory::GetDialog()->m_app->processEvents();
//    factory::GetDialog()->m_logScrollArea->verticalScrollBar()->setValue(factory::GetDialog()->m_logScrollArea->verticalScrollBar()->maximum());

}
