template <typename T>
struct Nodo {
    public:
        Nodo(T dato) : _dato(dato), _siguiente(nullptr), _anterior(nullptr) {}
        Nodo() = delete;

        T _dato;
        Nodo* _siguiente;
        Nodo* _anterior;
    };