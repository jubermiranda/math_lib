# **Coding Conventions**

**Version:** 1.0 **Last Updated:** 2025-10-14

## **1\. Philosophy**

The primary goal of these conventions is to promote **consistency, readability, and maintainability** across the entire codebase. A consistent style means developers can spend less time parsing code and more time understanding its logic.

While individual preferences may vary, adhering to the project's established style is mandatory.

## **2\. Naming Conventions**

The following naming scheme must be used to provide a clear distinction between namespaces, types, functions, and variables.

| Element | Convention | Example |
| :---- | :---- | :---- |
| **Namespaces** | `lowercase_snake_case` | `math_lib`, `core`, `analysis` |
| **Types (Classes, Structs, Enums)** | `UpperCamelCase` | `Analyzer`, `AnalysisCreateInfo` |
| **Enum Members** | `UPPER_SNAKE_CASE` | `LINEAR_INTERPOLATION` |
| **Functions & Methods** | `lowercase_snake_case` | `calculate_mean`, `create` |
| **Private Member Variables** | `m_` \+ `lowercase_snake_case` | `m_policy`, `m_generator` |
| **Constants (Global/Static)** | `k` \+ `lowercase_snake_case` | `const int k_max_iterations = 100;` |
| **Local Variables & Parameters** | `lowercase_snake_case` | `auto create_info = ...;` |

## **3\. Formatting and Style**

### **3.1. Indentation and Spacing**

* **Indentation:** Use **2 spaces** for each level of indentation. Do not use tabs.

### 

### **3.2. Brace Style (Hybrid Allman/K\&R)**

We employ a specific hybrid brace style to visually separate function definitions from other code blocks.

#### **Rule 1: Allman Style for Implementations**

The **Allman style** (opening brace `{` on a new line) is used **exclusively** for function, method, and constructor definitions.

This style makes the start and end of a function body clearly visible.

// Correct
std::unique\_ptr\<Analyzer\> Analyzer::create(const AnalysisCreateInfo& create\_info)
{
  return std::unique\_ptr\<Analyzer\>(new Analyzer(create\_info));
}

#### **Rule 2: K\&R Style for All Other Blocks**

The **K\&R style** (opening brace `{` on the same line) is used for **all other blocks**. This includes:

* Class, struct, and enum definitions (in `.h` files).
* Control flow statements (`if`, `else`, `for`, `while`, `switch`).
* Namespace blocks.

This style keeps the code compact and is the standard for declarations and control flow.

### **3.3. Line Breaking for Long Signatures**

To maintain readability for long function signatures, parameter lists, or member initializer lists, a specific indentation rule applies.

**The Rule:** Wrapped lines (parameters, initializers) are indented with **two levels (4 spaces)**. The function body begins after the opening Allman-style brace with **one level (2 spaces)**.

This clearly separates the function's signature and initialization from its implementation logic.

#### **Example: Constructor with Initializer List**

// Correct: Double indentation for wrapped initializers, single for body
MyClass::MyClass(const int param1, const double param2, const std::string& name) :
    m\_param1(param1), m\_param2(param2), m\_name(name)
{
  // Body starts with a single indentation level (2 spaces)
  if (m\_param1 \> 0\) {
    // ...
  }
}
// also correct:
MyClass::MyClass(
    const int param1, const double param2, const std::string& name
  ) :
    m\_param1(param1), m\_param2(param2), m\_name(name)
{
  // Body starts with a single indentation level (2 spaces)
  if (m\_param1 \> 0\) {
    // ...
  }
}
