using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab2_IDE
{

    public partial class Calculator : Form
    {
        Core core = new Core();

        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
                case 0x84:
                    base.WndProc(ref m);
                    if ((int)m.Result == 0x1)
                        m.Result = (IntPtr)0x2;
                    return;
            }

            base.WndProc(ref m);
        }

        public Calculator()
        {
            InitializeComponent();
        }

        private void ButtonClick(object sender, EventArgs e)
        {
            

            if (result.Text == "0" || core.GetOperationPressed())
            {
                result.Clear();
            }
            Button button = (Button)sender;
            core.SetNumber(result.Text + button.Text);
            result.Text = core.GetNumber();
            core.SetOperationPressed(false);
        }

        private void ButtonCE(object sender, EventArgs e)
        {
            result.Clear();
            result.Text = "0";
        }

        private void ButtonC(object sender, EventArgs e)
        {
            result.Text = "0";
        }

        private void ButtonOperation(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            core.SetOperation(button.Text);
            core.SetNumber1(result.Text);
            core.SetOperationPressed(true);

        }

        private void ButtonSqrt(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            core.SetOperation(button.Text);
            core.SqrtOperation(result.Text);
            core.SetOperationPressed(true);
            result.Text = (core.GetResult()).ToString();
        }

        private void ButtonPlusMinus(object sender, EventArgs e)
        {
            result.Text = core.PlusMinus(result.Text);
        }

        private void ButtonDelete(object sender, EventArgs e)
        {
            result.Text = core.DeleteButton(result.Text);
        }
  
        private void ButtonEqual(object sender, EventArgs e)
        {
            core.DoOperation();
            result.Text = core.GetResult().ToString();
            core.SetOperationPressed(false);
        }

        private void TextBox(object sender, EventArgs e)
        {

        }

        private void Close(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void Calculator_Load(object sender, EventArgs e)
        {

        }

        private void HoverCloseButton(object sender, EventArgs e)
        {
            pictureBox1.Image = Lab2_IDE.Properties.Resources.close1;
        }

        private void HoverButtonLeave(object sender, EventArgs e)
        {
            pictureBox1.Image = Lab2_IDE.Properties.Resources.close;

        }

        private void HoverMinimButton(object sender, EventArgs e)
        {
            pictureBox2.Image = Lab2_IDE.Properties.Resources.minimize1;
        }

        private void HoverLeaveButtonMin(object sender, EventArgs e)
        {
            pictureBox2.Image = Lab2_IDE.Properties.Resources.minimize;

        }
     
        private void panel2_DoubleClick(object sender, EventArgs e)
        {
            panel2.Location = new Point(302, 155);
        }

        private void panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void moreOperations(object sender, EventArgs e)
        {
            panel2.Location = new Point(213, 155);
        }

        private void ButtonDot(object sender, EventArgs e)
        {
            result.Text = core.dotButton(result.Text);
        }
    }
}
