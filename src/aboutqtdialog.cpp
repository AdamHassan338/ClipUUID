#include "aboutqtdialog.h"

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QCloseEvent>

AboutQtDialog::AboutQtDialog(QWidget *parent)
    : QDialog(parent)
{

    setWindowTitle(tr("About Qt"));
    qtIcon = QIcon(":/icons/qt.svg");
    setWindowIcon(qtIcon);

    dialogLayout = new QHBoxLayout(this);
    dialogLayout->setAlignment(Qt::AlignCenter);
    dialogLayout->setSpacing(15);
    setLayout(dialogLayout);

    QVBoxLayout* imageLayout = new QVBoxLayout();
    QLabel* image = new QLabel(this);
    image->setPixmap(qtIcon.pixmap(100));
    QSpacerItem* imageSpacer = new QSpacerItem(1,1,QSizePolicy::Minimum,QSizePolicy::Expanding);
    imageLayout->addWidget(image,0,Qt::AlignLeft);
    imageLayout->addSpacerItem(imageSpacer);

    dialogLayout->addLayout(imageLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    dialogLayout->addLayout(mainLayout);

    QVBoxLayout* textLayout = new QVBoxLayout();
    QLabel* titleLabel = new QLabel("<strong>About Qt</strong>", this);
    QFont big = titleLabel->font();
    big.setPixelSize(20);
    big.setBold(true);
    titleLabel->setFont(big);

    titleLabel->setAlignment(Qt::AlignLeft);
    textLayout->addWidget(titleLabel);

    QLabel* text = new QLabel(this);
    textLayout->addWidget(text);
    text->setText(QString(
        "<p>This program uses Qt version 6.7.3<br><br>"

        "Qt is a C++ toolkit for cross-platform application development.<br><br>"

        "Qt provides single-source portability across all major desktop operating systems. "
        "It is also available for embedded Linux and other embedded and mobile operating systems.<br><br>"

        "Qt is available under three different licensing options designed to accommodate the "
        "needs of our various users.<br><br>"

        "Qt licensed under our commercial license agreement is appropriate for development of "
        "proprietary/commercial software where you do not want to share any source code with third parties "
        "or otherwise cannot comply with the terms of the GNU LGPL version 3.<br><br>"

        "Qt licensed under the GNU LGPL version 3 is appropriate for the development of Qt "
        "applications provided you can comply with the terms and conditions of the GNU LGPL version 3.<br><br>"

        "Please see <a href=\"https://www.qt.io/licensing\">qt.io/licensing</a> for an overview of Qt licensing.<br><br>"
        "Copyright (C) 2024 The Qt Company Ltd and other contributors.<br><br>"

        "Qt and the Qt logo are trademarks of The Qt Company Ltd.<br><br>"

        "Qt is The Qt Company Ltd product developed as an open source project. See <a href=\"https://qt.io\">qt.io</a> for more information."
        ));

    text->setWordWrap(true);
    text->setOpenExternalLinks(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextBrowserInteraction);

    mainLayout->addLayout(textLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::hide);
    buttonLayout->addWidget(okButton,0,Qt::AlignRight);

    mainLayout->addLayout(buttonLayout);
}

void AboutQtDialog::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
