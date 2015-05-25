#ifndef PAGES
#define PAGES

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>
#include <QDateTimeEdit>
#include <QSpinBox>

class ConfigurationPage : public QWidget
{
public:
    ConfigurationPage(QWidget *parent = 0);
};

class QueryPage : public QWidget
{
public:
    QueryPage(QWidget *parent = 0);
};

class UpdatePage : public QWidget
{
public:
    UpdatePage(QWidget *parent = 0);
};

#endif // PAGES

