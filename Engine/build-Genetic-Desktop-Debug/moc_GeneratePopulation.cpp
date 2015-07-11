/****************************************************************************
** Meta object code from reading C++ file 'GeneratePopulation.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Genetic/include/GeneratePopulation.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeneratePopulation.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneratePopulation[] = {

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
      20,   19,   19,   19, 0x0a,
      36,   19,   19,   19, 0x0a,
      50,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GeneratePopulation[] = {
    "GeneratePopulation\0\0slot_get_file()\0"
    "slot_valide()\0slot_cancel()\0"
};

void GeneratePopulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeneratePopulation *_t = static_cast<GeneratePopulation *>(_o);
        switch (_id) {
        case 0: _t->slot_get_file(); break;
        case 1: _t->slot_valide(); break;
        case 2: _t->slot_cancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GeneratePopulation::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeneratePopulation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GeneratePopulation,
      qt_meta_data_GeneratePopulation, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneratePopulation::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneratePopulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneratePopulation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneratePopulation))
        return static_cast<void*>(const_cast< GeneratePopulation*>(this));
    return QDialog::qt_metacast(_clname);
}

int GeneratePopulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
