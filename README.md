# 🐖PiggyBank

## Object Oriented Programming Project

### About
This is an OOP project for a course at Faculty of Mathematics and Informatics of University of Bucharest. It's an C++ app that helps you keep evidence of the incomes or expenses you have. It has some simple functionalities like editing, adding or removing an evidence or selecting some specific evidence base on their dates and getting the balance. It also allows multiple accounts and users. The GUI is built using SFML library.

### Good to know
- in order to edit an evidence or simply delete it just double click on it
- if you enter wrong credentials when signing in an exception message occurs in the terminal and the form is cleared
- if you try to create an account that shares some credentials with another account you will also get an error and the sign up form will be cleared
- if you give some input that doesn't respect the specified format you will also get an exception and the form will be cleared
- you can select evidence that have their date in a range or at a specific date by specifing the date in the following format:
  - `dd/mm/yyyy` for a specific date
  - `dd/mm/yyyy-dd/mm/yyyy` for a range of dates
  - if you have more criteria just separate them by `;`; Example: `9/3/2022-14/3/2022;20/3/2022;1/2/2020-3/2/2022`
- if you enter invalid dates they will be adjusted; Example day 36 of month 2 (March) becomes day 5 of month 3 (April)  
- you can insert/pop character from a text area only at its end
- if the text enterd in a text area is longer than its maximum number of characters it can display the text area will show only the last charcters and the rest won't be lost 
- in order to commit changes to your account you have to press logout

### Sneak Peeks
- Welcome View </br> <img width="400" alt="WelcomeView" src="https://user-images.githubusercontent.com/93842197/164547428-b5729f80-e616-45d7-af25-5c4968fca57f.png">
- Sign Up View </br><img width="400" alt="SignUpView" src="https://user-images.githubusercontent.com/93842197/164547300-92c20204-9b19-44d1-acf1-f436b155c4b4.png">
- Sign In View </br> <img width="400" alt="SignInView" src="https://user-images.githubusercontent.com/93842197/164547273-563a6cfb-0734-498e-8548-37883d2cd964.png">
- New User Main View </br> <img width="400" alt="NewUserView" src="https://user-images.githubusercontent.com/93842197/164548381-8917e998-abab-468d-a1ac-b9f74e8595e0.png">
- Experienced User Main View </br> <img width="400" alt="MainView" src="https://user-images.githubusercontent.com/93842197/164547242-4cf454ce-d012-48b2-8139-65f03694e133.png">
- Add Evidence Form </br> <img width="400" alt="AddEvidenceForm" src="https://user-images.githubusercontent.com/93842197/164547150-078db636-1b2d-41f3-b35f-406ee00833f1.png">
- Filter Form </br> <img width="400" alt="FilterForm" src="https://user-images.githubusercontent.com/93842197/164547119-6f9baf87-be96-47e4-81ba-ba13ed9341b3.png">
- Update Form </br> <img width="400" alt="UpdateForm" src="https://user-images.githubusercontent.com/93842197/164546609-7e54587f-f7d4-4647-9e39-8fbe73d717a2.png">
- Balance </br> <img width="400" alt="Balance" src="https://user-images.githubusercontent.com/93842197/164547089-7f0dd234-b79f-4cf2-b0ee-b20a085ac4c8.png">
