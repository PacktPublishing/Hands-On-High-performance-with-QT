#ifndef SVGCACHE_H
#define SVGCACHE_H

#include <QSvgWidget>
#include <QSvgRenderer>
#include <QPainter>
#include <QMap>
#include <QDebug>


class SvgCache
{
public:
    void paintSvg(const QString& path, QSvgWidget& widget)
    {
        auto r = getChachedContents(path);

        QPainter p;
        p.begin(&widget);
        r->render(&p);
        p.end();
    }

    void paintSvg2(const QString& path, QSvgWidget& widget)
    {
        QSvgWidget v(path);
        //widget = v; // error!

        QPainter p(&widget);
        v.renderer()->render(&p);
    }

    QSvgRenderer* getChachedContents(const QString& path)
    {
        auto iter = svgMap_.constFind(path);
        if(iter == svgMap_.constEnd())
        {
            qDebug() << "SVG cache, loading '" << path <<"'";
            iter = svgMap_.insert(path, new QSvgRenderer(path));
        }

        return iter.value();
    }

private:
    QMap<QString, QSvgRenderer*> svgMap_;
};


class MySvgWidget
        : public QSvgWidget
{
public:
    MySvgWidget(QWidget *parent = nullptr)
        : QSvgWidget(parent)
    {}

    void useCache(const QString& path, SvgCache& cache)
    {
        cachedSvg_ = cache.getChachedContents(path);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        if(cachedSvg_)
        {
            QPainter p;
            p.begin(this);
            cachedSvg_->render(&p);
            p.end();
        }
        else
        {
            QSvgWidget::paintEvent(event);
        }
    }

private:
    QSvgRenderer* cachedSvg_ = nullptr;
};

#endif // SVGCACHE_H
