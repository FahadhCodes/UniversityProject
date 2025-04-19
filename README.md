# 🌟 **Customer Order Management System** 🌟

Welcome to the **Customer Order Management System**, a dynamic and feature-rich application built in **C** to manage customer orders, products, and billing efficiently. This project is designed to handle customer data, track orders, calculate delivery dates, and generate detailed bills.

---

## 🎯 **Features**
### ✅ **Customer Management**
- Add, update, delete, and search customer details.
- Track customer orders with unique IDs.

### ✅ **Product Management**
- Add, update, and delete products dynamically for each customer.
- Recalculate total prices for products in real-time.

### ✅ **Billing System**
- Generate detailed bills with:
  - Ordered and delivered dates.
  - Product names and prices.
  - Total price calculation.
- Save bills to files for future reference.

### ✅ **Delivery Tracking**
- Calculate delivery dates based on work time periods (hours, days, months).
- Display ordered and delivered dates in a user-friendly format.

### ✅ **File Handling**
- Maintain a database of all customer transactions in a text file (`database.txt`).
- Save individual customer bills in a structured folder.

### ✅ **User-Friendly Interface**
- Menu-driven interface with **color-coded options** for better usability.
- Robust error handling and prompts for invalid inputs.

---

## 🛠️ **Technologies Used**
- **Programming Language:** C
- **Libraries:**
  - `<stdio.h>` for input/output operations.
  - `<stdlib.h>` for dynamic memory allocation.
  - `<string.h>` for string manipulation.
  - `<time.h>` for date and time handling.
  - `<windows.h>` for color-coded console outputs (Windows-specific).

---

## 📂 **Project Structure**
```
📁 Mini-Project
├── 📁 Customers Bills
│   ├── 📁 Database
│   │   └── database.txt
│   └── Individual Bills (Generated dynamically)
├── App.c
└── README.md
```

---

## 🚀 **How to Run**
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-repo/customer-order-management.git
   cd customer-order-management
   ```

2. **Compile the Code:**
   Use a C compiler like GCC:
   ```bash
   gcc App_v4.c -o CustomerOrderSystem
   ```

3. **Run the Program:**
   ```bash
   ./CustomerOrderSystem
   ```

4. **Follow the Menu:**
   - Choose options like `INSERT`, `UPDATE`, `DELETE`, `SEARCH`, or `DISPLAY` to interact with the system.

---

## 📖 **How It Works**
### **1. Menu Options**
- **INSERT:** Add customer data using `FRONT`, `REAR`, or `NEXT` methods.
- **UPDATE:** Modify customer details, products, or delivery dates.
- **DELETE:** Remove customer data or specific products.
- **SEARCH:** Find customer details by their unique ID.
- **DISPLAY:** View all customer data and their orders.

### **2. Billing**
- Generate bills for customers with detailed product and price information.
- Save bills in the `Customers Bills` folder for future reference.

### **3. Delivery Tracking**
- Calculate delivery dates dynamically based on work time periods.
- Display ordered and delivered dates in a readable format.

---

## 🎨 **Color-Coded Interface**
The system uses **color-coded outputs** for better readability:
- **Green**
- **Red**
- **Blue**
- **Yellow**

---

## 📊 **Example Output**
### **Menu:**
```plaintext
+-----------------------------------------------------------------------------------------------------------------------------------+
|                                                              MENU                                                                 |
+-----------------------------------------------------------------------------------------------------------------------------------+
ENTER WHAT YOU WANT TO CHANGE INSERT UPDATE DELETE SEARCH DISPLAY :
```

### **Bill Example:**
```plaintext
+------------------------------------------+
|                     BILL                 |
+------------------------------------------+
|   John Doe          |   123456789        |
+------------------------------------------+
| ORDERED DATE   : 18 /04 /2025 |12:00 PM  |
| DELIVERED DATE : 20 /04 /2025 |12:00 PM  |
+------------------------------------------+
|      PRODUCT        |       PRICE        |
+------------------------------------------+
|      Laptop         |       1000         |
|      Phone          |        500         |
+------------------------------------------+
|      TOTAL          |       1500         |
+------------------------------------------+
```

---

## 🛠️ **Functions Overview**
### **Core Functions**
- **`user_inp`:** Handles customer input and initializes their data.
- **`insertFront`, `insertRear`, `insertNext`:** Add customer data at different positions in the list.
- **`update`:** Modify customer or product details.
- **`delete`:** Remove customer data or specific products.
- **`search`:** Find customer details by their unique ID.
- **`display`:** Show all customer data and their orders.

### **Product Management**
- **`insertProduct_Rear`:** Add products to a customer's order.
- **`pupdate`:** Update product details.
- **`pdelete`:** Remove a product from a customer's order.
- **`priceRecalculator`:** Recalculate the total price of products.

### **Billing**
- **`billPrinting`:** Generate and save detailed bills for customers.
- **`print_Display`:** Save all customer data to a database file.

---

## 🌟 **Future Enhancements**
- **Graphical User Interface (GUI):** Replace the console-based interface with a modern GUI.
- **Database Integration:** Use a database like MySQL or SQLite for better data management.
- **Multi-User Support:** Add authentication and role-based access for admins and staff.
- **Analytics Dashboard:** Provide insights into sales trends and customer behavior.

---

## 📬 **Contact**
Feel free to reach out if you have any questions or suggestions:
- **Email:** fahad.work2948@gmail.com
- **GitHub:** [FahadhCodes](https://github.com/FahadhCodes)
- **LinkedIn:** [Fahadh Muhammadh](https://linkedin.com/in/fahadworks)
