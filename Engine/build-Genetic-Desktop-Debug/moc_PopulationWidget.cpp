/****************************************************************************
** Meta object code from reading C++ file 'PopulationWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Genetic/include/PopulationWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PopulationWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PopulationWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      33,   17,   17,   17, 0x0a,
      47,   17,   17,   17, 0x0a,
      59,   17,   17,   17, 0x0a,
      72,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PopulationWidget[] = {
    "PopulationWidget\0\0generate_pop()\0"
    "indject_pop()\0clear_pop()\0update_pop()\0"
    "export_ind()\0"
};

void PopulationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PopulationWidget *_t = static_cast<PopulationWidget *>(_o);
        switch (_id) {
        case 0: _t->generate_pop(); break;
        case 1: _t->indject_pop(); break;
        case 2: _t->clear_pop(); break;
        case 3: _t->update_pop(); break;
        case 4: _t->export_ind(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PopulationWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PopulationWidget::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_PopulationWidget,
      qt_meta_data_PopulationWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PopulationWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PopulationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PopulationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PopulationWidget))
        return static_cast<void*>(const_cast< PopulationWidget*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int PopulationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
