/****************************************************************************
** Meta object code from reading C++ file 'ListOpen.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Virtin/include/ListOpen.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ListOpen.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ListOpen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x0a,
      39,    9,    9,    9, 0x0a,
      71,   69,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ListOpen[] = {
    "ListOpen\0\0point\0execContexMenu(QPoint)\0"
    "menu_folder_clicked(QAction*)\0,\0"
    "rename(QModelIndex,QModelIndex)\0"
};

void ListOpen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ListOpen *_t = static_cast<ListOpen *>(_o);
        switch (_id) {
        case 0: _t->execContexMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->menu_folder_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->rename((*reinterpret_cast< QModelIndex(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ListOpen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ListOpen::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_ListOpen,
      qt_meta_data_ListOpen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ListOpen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ListOpen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ListOpen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ListOpen))
        return static_cast<void*>(const_cast< ListOpen*>(this));
    return QTreeView::qt_metacast(_clname);
}

int ListOpen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
