/****************************************************************************
** Meta object code from reading C++ file 'StateWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Genetic/include/StateWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StateWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      21,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   12,   12,   12, 0x0a,
      40,   12,   12,   12, 0x0a,
      58,   51,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StateWidget[] = {
    "StateWidget\0\0begin()\0end()\0slot_start()\0"
    "time_out()\0engine\0up_machine(VirtualMachine*)\0"
};

void StateWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StateWidget *_t = static_cast<StateWidget *>(_o);
        switch (_id) {
        case 0: _t->begin(); break;
        case 1: _t->end(); break;
        case 2: _t->slot_start(); break;
        case 3: _t->time_out(); break;
        case 4: _t->up_machine((*reinterpret_cast< VirtualMachine*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StateWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StateWidget::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_StateWidget,
      qt_meta_data_StateWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StateWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StateWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StateWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StateWidget))
        return static_cast<void*>(const_cast< StateWidget*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int StateWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void StateWidget::begin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void StateWidget::end()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
