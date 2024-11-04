#ifndef UUIDGENORATOR_H
#define UUIDGENORATOR_H

#include <QObject>
#include <QUuid>
#include <QString>

class UUIDGenorator : public QObject
{
    Q_OBJECT
public:
    explicit UUIDGenorator(QObject *parent = nullptr);

    Q_PROPERTY(QString UUID READ UUID WRITE setUUID NOTIFY UUIDChanged FINAL)
    QString UUID() const;
    void setUUID(const QString &newUUID);

public slots:
    Q_INVOKABLE QString generateUuid();
    void requestFocus();

signals:
    void UUIDChanged();
    void focus();

private:
    QString m_UUID;
};

#endif // UUIDGENORATOR_H
