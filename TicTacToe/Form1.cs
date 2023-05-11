using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace TicTacToe
{
    public partial class TicTacToe : Form
    {
        const string path = @"..\..\..\x64\Debug\Minimax.dll";
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        static extern int getWinner(int[,] field);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        static extern int getNextMove(int[,] field, ref int x, ref int y);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        static extern bool isDraw(int[,] field);
        int[,] field =
        {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };
        Button[,] buttons = new Button[3, 3];
        public TicTacToe()
        {
            InitializeComponent();
            buttons[0, 0] = x0y0;
            buttons[0, 1] = x0y1;
            buttons[0, 2] = x0y2;
            buttons[1, 0] = x1y0;
            buttons[1, 1] = x1y1;
            buttons[1, 2] = x1y2;
            buttons[2, 0] = x2y0;
            buttons[2, 1] = x2y1;
            buttons[2, 2] = x2y2;
            x0y0.Name = "00";
            x0y1.Name = "01";
            x0y2.Name = "02";
            x1y0.Name = "10";
            x1y1.Name = "11";
            x1y2.Name = "12";
            x2y0.Name = "20";
            x2y1.Name = "21";
            x2y2.Name = "22";
        }

        private void Clear()
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0;  j < 3; j++)
                {
                    buttons[i, j].Text = "";
                    field[i, j] = 0;
                }
            }

            turn.Text = "X";
        }

        private void AskRestart(string prompt)
        {
            if (MessageBox.Show(prompt, "Tic Tac Toe") != DialogResult.OK)
            {
                Close();
                return;
            }

            Clear();
        }

        private void click(object sender, EventArgs e)
        {
            Console.WriteLine(System.IO.Directory.GetCurrentDirectory());
            Button button = (Button)sender;

            if (!string.IsNullOrEmpty(button.Text))
            {
                return;
            }

            int x = button.Name[0] - '0';
            int y = button.Name[1] - '0';
            field[x, y] = 1;

            button.Text = "X";

            if (getWinner(field) == 1)
            {
                AskRestart("Xs win!");
                return;
            }
            else if (isDraw(field))
            {
                AskRestart("Draw!");
                return;
            }

            turn.Text = "O";

            Update();

            int xO = 1, yO = 1;
            getNextMove(field, ref xO, ref yO);

            field[xO, yO] = -1;
            buttons[xO, yO].Text = "O";

            if (getWinner(field) == -1)
            {
                AskRestart("Os win!");
                return;
            }

            turn.Text = "X";
        }


    }
}
