//
//  dialog.cpp
//  BlockChain
//
//  Created by Chung-kaiYang on 12/29/17.
//

#include <iostream>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <dialog.h>

dialog::dialog(QWidget *parent)
:QDialog(parent)
{
    m_mainLayout = new QGridLayout(this);
    m_layout1 = new QHBoxLayout(this);
    m_layout2 = new QHBoxLayout(this);

    m_label1 = new QLabel("Label 1");
    m_label2 = new QLabel("Label 2");
    m_layout1->addWidget(m_label1);
    m_layout1->addWidget(m_label2);
    m_label3 = new QLabel("Label 3");
    m_label4 = new QLabel("Label 4");
    m_layout2->addWidget(m_label3);
    m_layout2->addWidget(m_label4);

    m_logLabel = new QLabel("BlockChain implementation by Clark Yang");
//    m_logLabel = new QLabel("BlockChain implementation by Clark Yang\n2nd line\n3rd line");
    m_scrollArea = new QScrollArea;
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollArea->resize (5, 5);
    m_scrollArea->setWidget(m_logLabel);

    m_mainLayout->addLayout(m_layout1, 0, 0);
    m_mainLayout->addLayout(m_layout2, 1, 0);
    m_mainLayout->addWidget(m_scrollArea, 2, 0);
    m_mainLayout->setRowStretch(0, 3);
    m_mainLayout->setRowStretch(1, 3);
    m_mainLayout->setRowStretch(2, 1);
}

dialog::~dialog()
{
    delete(m_mainLayout);
    delete(m_layout1);
    delete(m_layout2);
    delete(m_label1);
    delete(m_label2);
    delete(m_label3);
    delete(m_label4);
    delete(m_logLabel);
    delete(m_scrollArea);
}

void dialog::AppendLog(const string& log)
{
    //TBD
    m_logLabel->setText(m_logLabel->text() + "\n" + log.c_str());
    m_logLabel->repaint();
}

