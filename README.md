# PC1---Algo-Estruc
# Algoritmos

---

# Requisitos

## 1. Inicio de sesión.

### 1.1. Log in

- DNI (**string**)
- Contraseña (**string**)

### 1.2. Sign in

**(ArchivoUsuarios)**

- número de DNI (**string**)
- Fecha de nacimiento **(string)**
- Nombres **(string)**
- Apellidos **(string)**
- Teléfono **(string)**
- **Contraseña (string)**

## 2. En la app

### 2.1. Citas

- Al usuario le asignan una **fecha** para su chequeo médico
- Vista de los doctores y sus especializaciones.

### 2.2. Recetas (medicamentos)

**Sólo lectura**

- Antes
- Ahora

### 2.3. Atención

**3 bases de datos (archivos01)**

- Externa
- Emergencia
- Hospitalización

### 2.4. Solicitudes

- Recita **(agenda la cita para otro día) (archivo 02)**
    - El usuario elige entre todas las fechas, la que más le convenga (Listado de fechas).
- Interconsulta ( el médico general deriva a la persona a una especialidad)**(archivo03)** .
    - **Solo lectura** (el usuario mira a que especialista fue derivado).d
- Referencia ( Hospital A → Hospital B)**(archivo04)**
    - **Solo lectura** (el usuario mira a que hospital fue derivado).
