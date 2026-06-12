class ExpenseManager:
    def __init__(self):
        self.expenses = []

    def add_expense(self):
        name = input("Enter expense name: ")
        amount = float(input("Enter amount: "))
        category = input("Enter category: ")

        expense = {
            "name": name,
            "amount": amount,
            "category": category
        }

        self.expenses.append(expense)
        print("Expense added successfully. hehe\n")

    def view_expenses(self):
        if not self.expenses:
            print("No expenses found. yayayyaya :0\n")
            return

        for i, z in enumerate(self.expenses, start=1):
            print(f"{i}. {z['name']} - ₹{z['amount']} ({z['category']})")
        print()

    def search_expense(self):
        keyword = input("Enter expense name to search: ").lower()

        found = False

        for z in self.expenses:
            if keyword in z["name"].lower():
                print(f"{z['name']} - ₹{z['amount']} ({z['category']})")
                found = True

        if not found:
            print("No matching expense found. sed :(\n")
        else:
            print()

    def update_expense(self):
        self.view_expenses()
        if not self.expenses:
            return

        index = int(input("Enter expense number to update: ")) - 1

        if 0 <= index < len(self.expenses):
            self.expenses[index]["name"] = input("New name: ")
            self.expenses[index]["amount"] = float(input("New amount: "))
            self.expenses[index]["category"] = input("New category: ")
            print("Honesty is the best policy. Expense updated successfully! \n")
        else:
            print("Invalid choice. Choose something sensible -_- \n")

    def delete_expense(self):
        self.view_expenses()
        if not self.expenses:
            return

        index = int(input("Enter expense number to delete: ")) - 1

        if 0 <= index < len(self.expenses):
            self.expenses.pop(index)
            print("Expense deleted successfully! :)\n")
        else:
            print("Invalid Choice. Think better :(\n")


def main():
    manager = ExpenseManager()

    while True:
        print("Expense Manager")
        print("1. Add Expense")
        print("2. View Expenses")
        print("3. Search Expense")
        print("4. Update Expense")
        print("5. Delete Expense")
        print("6. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            manager.add_expense()
        elif choice == "2":
            manager.view_expenses()
        elif choice == "3":
            manager.search_expense()
        elif choice == "4":
            manager.update_expense()
        elif choice == "5":
            manager.delete_expense()
        elif choice == "6":
            print("Exiting program...")
            break
        else:
            print("Invalid choice. Try again. Try try but don't cry.\n")


main()