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
#include "dialog.h"
#include "factory.h"
#include "blockchain.h"

dialog::dialog(QWidget *parent, QApplication* app)
:QDialog(parent), m_app(app)
{
    assert(m_app);
    m_mainLayout = new QGridLayout(this);
    m_layout1 = new QHBoxLayout(this);
    m_blockChainListLayout = new QVBoxLayout(this);

    m_label1 = new QLabel("Label 1");
    m_label2 = new QLabel("Label 2");
    m_layout1->addWidget(m_label1);
    m_layout1->addWidget(m_label2);
    m_blockChainLabel = new QLabel("Current Block Chain");
    m_blockChainList = new QLabel("Empty");
    m_blockChainScrollArea = new QScrollArea;
    m_blockChainScrollArea->setWidget(m_blockChainList);
    m_blockChainListLayout->addWidget(m_blockChainLabel);
    m_blockChainListLayout->addWidget(m_blockChainScrollArea);
    m_blockChainListLayout->setStretch(0, 1);
    m_blockChainListLayout->setStretch(1, 10);

    m_logLabel = new QLabel("QT initialized.");
    m_logLabel->setStyleSheet("QLabel { background-color:transparent; color : lime; }");
    m_logScrollArea = new QScrollArea;
    m_logScrollArea->setStyleSheet("background-color:black;");
    m_logScrollArea->resize (5, 5);
    m_logScrollArea->setWidget(m_logLabel);

    m_mainLayout->addLayout(m_layout1, 0, 0);
    m_mainLayout->addLayout(m_blockChainListLayout, 1, 0);
    m_mainLayout->addWidget(m_logScrollArea, 2, 0);
    m_mainLayout->setRowStretch(0, 1);
    m_mainLayout->setRowStretch(1, 4);
    m_mainLayout->setRowStretch(2, 2);
}

dialog::~dialog()
{
    delete(m_mainLayout);
    delete(m_layout1);
    delete(m_blockChainListLayout);
    delete(m_label1);
    delete(m_label2);
    delete(m_blockChainLabel);
    delete(m_blockChainList);
    delete(m_blockChainScrollArea);
    delete(m_logLabel);
    delete(m_logScrollArea);
}

void dialog::AppendLog(const string& log)
{
    m_logLabel->setText(m_logLabel->text() + "\n" + log.c_str());
    m_logLabel->adjustSize();
    m_logScrollArea->widget()->resize(m_logScrollArea->widget()->sizeHint());
    m_app->processEvents();
    m_logScrollArea->verticalScrollBar()->setValue(m_logScrollArea->verticalScrollBar()->maximum());
}

void dialog::UpdateBlockChainList()
{
    m_blockChainList->setText(factory::GetBlockChain()->getChainInfo(true).c_str());
    m_blockChainList->adjustSize();
    m_blockChainScrollArea->widget()->resize(m_blockChainScrollArea->widget()->sizeHint());
    m_app->processEvents();
    m_blockChainScrollArea->verticalScrollBar()->setValue(m_blockChainScrollArea->verticalScrollBar()->maximum());
}

