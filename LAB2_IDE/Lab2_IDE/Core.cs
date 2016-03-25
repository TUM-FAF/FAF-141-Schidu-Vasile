using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;




namespace Lab2_IDE
{
    class Core
    {

        //Varialbe declaration
        private int lineNumber = 5;
        private string number = "";
        private string number1 = "";
        private double result = 0;
        private string operation = "";
        private bool operationPressed = false;
        private bool operationPressed1 = false;
        bool isNegative = false;
        bool powButtonPressed = false;
        bool dotPressed = false;
        private string longExpression = "";


        //Function declaration

  

        public void SetIsNegative(bool sign)
        {
            this.isNegative = sign; 
        }

        public void SetDotPressed(bool ok)
        {
            this.dotPressed = ok;
        }

        public bool GetCommaPressed()
        {
            return this.dotPressed;
        }

        public bool GetIsNegative()
        {
            return this.isNegative;
        }

        public void SetOperation(string oper)
        {
            this.operation = oper;
        }

        public string GetOperation()
        {
            return this.operation;
        }

        public double GetResult()
        {
            return this.result;
        }

        public void SetNumber(string exp)
        {
            this.number = exp;
        }

        public string GetNumber()
        {
            return this.number;
        }

        public void SetNumber1(string exp)
        {
            this.number1 = exp;
        }

        public string GetNumber1()
        {
            return this.number1;
        }

        public void SetOperationPressed(bool oper)
        {
            this.operationPressed = oper;
        }

        public bool GetOperationPressed()
        {
            return this.operationPressed;
        }

        public string DeleteButton(string expresion)
        {
            if (expresion.ToString().Length == 1)
            {
                return "0";
            }
            if (expresion == "0")
            {
                return "0";
            }
            return expresion.Remove(expresion.Length - 1);
        }

        public string PlusMinus(string expresion)
        {
            if (expresion.StartsWith("-"))
            {
                expresion = expresion.Substring(1);
                return expresion;
            }
            else if (!string.IsNullOrEmpty(expresion) && decimal.Parse(expresion) != 0)
            {
                expresion = "-" + expresion;
                return expresion;
            }
            else
            {
                return expresion;
            }
        }

        public string dotButton(string expresion)
        {
            if (expresion.EndsWith(".")) 
            {
                return expresion;
            }
            else if (!string.IsNullOrEmpty(expresion) && decimal.Parse(expresion) != 0)
            {
                expresion = expresion + ".";
                return expresion;
            }
            else
            {
                return expresion;
            }

        }

        public void DoOperation()
        {

            switch (operation)
            {
                
                case "+":

                    result = Double.Parse(this.number1) + Double.Parse(this.number);
                    break;
                case "-":
                    result = Double.Parse(this.number1) - Double.Parse(this.number);
                    break;
                case "/":
                    result = Double.Parse(this.number1) / Double.Parse(this.number);
                    break;
                case "*":
                    result = Double.Parse(this.number1) * Double.Parse(this.number);
                    break;
                case "pow":
                    result = Math.Pow(Double.Parse(this.number1), Double.Parse(this.number));
                    break;
                default:
                    break;
            }
            operationPressed = false;
        }

        public void SqrtOperation(string number)
        {
            switch (operation)
            {
                case "sin":
                    result = Math.Sin(Double.Parse(number));
                    break;
                case "cos":
                    result = Math.Cos(Double.Parse(number));
                    break;
                case "tan":
                    result = Math.Tan(Double.Parse(number));
                    break;
                case "log":
                    result = Math.Log(Double.Parse(number));
                    break;
                case "sqrt":
                    result = Math.Sqrt(Double.Parse(number));
                    break;
            }
        }
    }
}
