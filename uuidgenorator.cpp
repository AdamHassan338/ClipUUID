#include "uuidgenorator.h"

#include <QDebug>
#include <QClipboard>
#include <QGuiApplication>
UUIDGenorator::UUIDGenorator(QObject *parent)
    : QObject{parent}
{
    generateUuid();
}

QString UUIDGenorator::generateUuid(){
    setUUID(QUuid::createUuid().toString());
    QGuiApplication::clipboard()->setText(m_UUID);
    return m_UUID;
}

QString UUIDGenorator::UUID() const
{
    return m_UUID;
}

void UUIDGenorator::setUUID(const QString &newUUID)
{
    if (m_UUID == newUUID)
        return;
    m_UUID = newUUID;
    emit UUIDChanged();
}
