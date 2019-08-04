#include "urlinterceptor.h"

UrlInterceptor::UrlInterceptor()
    :QObject(nullptr)
    ,QQmlAbstractUrlInterceptor()
{
}

QUrl UrlInterceptor::intercept(const QUrl &path, QQmlAbstractUrlInterceptor::DataType type)
{
    Q_UNUSED(type)
    if(!path.toLocalFile().isEmpty()) {
        emit newFile(path);
    }
    return path;
}

UrlInterceptor* UrlInterceptor::self()
{
    static UrlInterceptor self;
    return &self;
}

UrlInterceptor::~UrlInterceptor() = default;
