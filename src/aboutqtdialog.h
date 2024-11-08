#ifndef ABOUTQTDIALOG_H
#define ABOUTQTDIALOG_H

#include <QDialog>

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QSpacerItem;
class AboutQtDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutQtDialog(QWidget *parent = nullptr);

private:
    QHBoxLayout* dialogLayout;
    QVBoxLayout* imageLayout;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonLayout;

    QLabel* image;
    QSpacerItem* imageSpacer;
    QVBoxLayout* textLayout;
    QLabel* titleLabel;
    QLabel* text;

    QPushButton* okButton;

    QIcon qtIcon;


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

};

#endif // ABOUTQTDIALOG_H
