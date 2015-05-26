#include "pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox * configGroup = new QGroupBox(tr("Item lifecicle"));

    QLabel * deleteLabel = new QLabel(tr("Delete:"));
    QPushButton * deleteButton = new QPushButton(tr("remove item"));

    QHBoxLayout * deleteLayout = new QHBoxLayout;
    deleteLayout->addWidget(deleteLabel);
    deleteLayout->addWidget(deleteButton);

    QVBoxLayout * configLayout = new QVBoxLayout;
    configLayout->addLayout(deleteLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(itemRemoved()));
}

void ConfigurationPage::itemRemoved()
{
    emit deleteItem();
    close();
}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox * updateGroup = new QGroupBox(tr("Shape modifiction"));
    QPushButton * changeBrushFill = new QPushButton(tr("Fill shape"));
    QCheckBox * appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox * docsCheckBox = new QCheckBox(tr("Update documentation"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(changeBrushFill);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(changeBrushFill, SIGNAL(clicked(bool)), this, SLOT(shapeUpdated()));
}

void UpdatePage::shapeUpdated()
{
    QColor color(QColorDialog::getColor(Qt::white));
    QBrush brush(color);
    emit updateShape(brush);
}
