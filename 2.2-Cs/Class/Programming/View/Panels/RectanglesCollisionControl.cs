using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using Programming.Model.Classes;
using Rectangle = Programming.Model.Classes.Rectangle;

namespace Programming.Model.Panels
{
    public partial class RectanglesCollisionControl : UserControl
    {

        private Color COLLISION_COLOR = Color.Pink;
        private Color NORMAL_COLOR = Color.LightGreen;

        /// <summary>
        /// Хранит переменную для подсказок пользователю.
        /// </summary>
        private ToolTip _toolTip = new ToolTip();

        /// <summary>
        /// Хранит список прямоугольников.
        /// </summary>
        private List<Rectangle> _rectangles = new List<Rectangle>();

        /// <summary>
        /// Хранит переменную с текущим прямоугольником.
        /// </summary>
        private Rectangle _currentRectangle;

        /// <summary>
        /// Хранит список нарисованных панелей.
        /// </summary>
        private List<Panel> _rectanglePanels = new List<Panel>();

        /// <summary>
        /// Метод позволяющий получить строку со всей информацией о прямоугольнике.
        /// </summary>
        /// <param name="rectangle"></param>
        /// <returns></returns>
        private string GetInfoOfRectangle(Rectangle rectangle)
        {
            return $"{rectangle.Id}: (" +
                    $"X = {rectangle.Centre.X}; Y = {rectangle.Centre.Y};" +
                    $" W = {rectangle.Width}; H = {rectangle.Height})";
        }

        /// <summary>
        /// Метод для добавления прямоугольника в лист бокс.
        /// </summary>
        /// <param name="rectangle">Прямоугольник нужный для добавления.</param>
        private void ItemAddListBox(Rectangle rectangle)
        {
            _rectangles.Add(rectangle);
            RectanglesListBox.Items.Add(GetInfoOfRectangle(rectangle));
        }

        /// <summary>
        /// Обновление информации о прямоугольнике
        /// </summary>
        /// <param name="rectangle">Прямоугольник информацию о котором нужно обновить.</param>
        private void UpdateRectanglesInfo(Rectangle rectangle)
        {
            RectanglesListBox.Items[RectanglesListBox.SelectedIndex] = (GetInfoOfRectangle(rectangle));
        }

        /// <summary>
        /// Метод добавления прямоугольника.
        /// </summary>
        /// <param name="rectangle">Прямоугольник, который будут добавлять.</param>
        private void AddRectangleToPanel(Rectangle rectangle)
        {
            Panel panel = new Panel();
            panel.Location = new Point(rectangle.Centre.X, rectangle.Centre.Y);
            panel.Size = new Size(rectangle.Width, rectangle.Height);
            panel.BackColor = NORMAL_COLOR;
            _rectanglePanels.Add(panel);
            CanvasPanel.Controls.Add(panel);
        }

        /// <summary>
        /// Изменение локации панели.
        /// </summary>
        /// <param name="panel"></param>
        private void ChangedRectanglePanel(Panel panel)
        {
            panel.Location = new Point(_currentRectangle.Centre.X, _currentRectangle.Centre.Y);
            panel.Size = new Size(_currentRectangle.Width, _currentRectangle.Height);
        }

        /// <summary>
        /// Методя для удаления прямоугольника из списка и с панели.
        /// </summary>
        private void DeleteRectangle()
        {
            if (RectanglesListBox.Items.Count != 0)
            {
                _rectangles.RemoveAt(RectanglesListBox.SelectedIndex);
                CanvasPanel.Controls.Remove(_rectanglePanels[RectanglesListBox.SelectedIndex]);
                _rectanglePanels.RemoveAt(RectanglesListBox.SelectedIndex);
                RectanglesListBox.Items.RemoveAt(RectanglesListBox.SelectedIndex);
                if (RectanglesListBox.Items.Count != 0)
                {
                    RectanglesListBox.SelectedIndex = 0;
                }
            }
        }

        /// <summary>
        /// Метод для очищения всех текстбоксов.
        /// </summary>
        private void ClearRectangleInfo()
        {
            RectangleIdTextBox.Clear();
            RectangleYTextBox.Clear();
            RectangleWidthTextBox.Clear();
            RectangleHeightTextBox.Clear();
            RectangleXTextBox.Clear();
            ValueRectangleSquareLabel.Text = "0";
            ValueCircleRadiusLabel.Text = "0";
            ValueIsSquareLabel.Text = "No";
        }

        /// <summary>
        /// Метод для поиска пересечения прямоугольников.
        /// </summary>
        private void FindCollisions()
        {
            for (int i = 0; i < _rectanglePanels.Count; i++)
            {
                _rectanglePanels[i].BackColor = NORMAL_COLOR;
            }
            for (int i = 0; i < _rectanglePanels.Count; i++)
            {
                for (int g = i + 1; g < _rectanglePanels.Count; g++)
                {
                    if (CollisionManager.IsCollision(_rectangles[i], _rectangles[g]))
                    {
                        _rectanglePanels[i].BackColor = COLLISION_COLOR;
                        _rectanglePanels[g].BackColor = COLLISION_COLOR;
                    }
                }
            }
            CheckOnFirstQuater();
        }

        private void CheckOnFirstQuater()
        {
            if(_currentRectangle != null)
            {
               double rightLowerPointX = _currentRectangle.Centre.X + _currentRectangle.Width / 2;
               double rightLowerPointY = _currentRectangle.Centre.Y + _currentRectangle.Height / 2;
                bool isFirstQuater = rightLowerPointX >= CanvasPanel.Width / 2 && rightLowerPointY <= CanvasPanel.Height / 2;
                IsFirstQuaterLabel.Text = isFirstQuater ? "Yes" : "No";
            }
        }

        public RectanglesCollisionControl()
        {
            InitializeComponent();
            DrawStripes();
            RectangleIdTextBox.ReadOnly = true;
        }

        private void RectanglesAddButton_MouseHover(object sender, EventArgs e)
        {
            RectanglesAddButton.Image = Properties.Resources.rectangle_add_24x24;
        }

        private void RectanglesAddButton_MouseLeave(object sender, EventArgs e)
        {
            RectanglesAddButton.Image = Properties.Resources.rectangle_add_24x24_uncolor;
        }

        private void RectanglesAddButton_MouseEnter(Object sender, EventArgs e)
        {
            RectanglesAddButton.Image = Properties.Resources.rectangle_add_24x24;
        }

        private void RectanglesAddButton_Click(object sender, EventArgs e)
        {
            Rectangle rectangle = RectangleFactory.Randomize(CanvasPanel.Size.Width, CanvasPanel.Size.Height);
            rectangle.Id = rectangle.Id;
            rectangle.Centre.X = Math.Abs(rectangle.Centre.X - rectangle.Width);
            rectangle.Centre.Y = Math.Abs(rectangle.Centre.Y - rectangle.Height);
            ItemAddListBox(rectangle);
            AddRectangleToPanel(rectangle);
            RectanglesListBox.SelectedIndex = RectanglesListBox.Items.Count - 1;
            FindCollisions();
        }

        private void RectangleDeleteButton_Click(object sender, EventArgs e)
        {
            DeleteRectangle();
            FindCollisions();
        }

        private void RectanglesDeleteButton_MouseHover(object sender, EventArgs e)
        {
            RectangleDeleteButton.Image = Properties.Resources.rectangle_remove_24x24;
        }

        private void RectanglesDeleteButton_MouseLeave(object sender, EventArgs e)
        {
            RectangleDeleteButton.Image = Properties.Resources.rectangle_remove_24x24_uncolor;
        }

        private void RectanglesDeleteButton_MouseEnter(Object sender, EventArgs e)
        {
            RectangleDeleteButton.Image = Properties.Resources.rectangle_remove_24x24;
        }

        private void RectanglesListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (RectanglesListBox.SelectedIndex != -1)
            {
                _currentRectangle = _rectangles[RectanglesListBox.SelectedIndex];
                RectangleIdTextBox.Text = _currentRectangle.Id.ToString();
                RectangleWidthTextBox.Text = _currentRectangle.Width.ToString();
                RectangleHeightTextBox.Text = _currentRectangle.Height.ToString();
                RectangleXTextBox.Text = _currentRectangle.Centre.X.ToString();
                RectangleYTextBox.Text = _currentRectangle.Centre.Y.ToString();
                ValueRectangleSquareLabel.Text = _currentRectangle.Square().ToString();
                ValueCircleRadiusLabel.Text = _currentRectangle.GetCircleRadius().ToString();
                ValueIsSquareLabel.Text = _currentRectangle.IsSquare() ? "Yes" : "No";
            }
            else
            {
                ClearRectangleInfo();
            }
        }

        private void RectanglesWidthTextBox_TextChanged(object sender, EventArgs e)
        {
            RectangleWidthTextBox.BackColor = Color.White;
            if (string.IsNullOrEmpty(RectangleWidthTextBox.Text) == false && RectanglesListBox.Items.Count != 0)
            {
                try
                {
                    _currentRectangle.Width = Int32.Parse(RectangleWidthTextBox.Text);
                    _toolTip.SetToolTip(RectangleWidthTextBox, "");
                    ChangedRectanglePanel(_rectanglePanels[RectanglesListBox.SelectedIndex]);
                    UpdateRectanglesInfo(_currentRectangle);
                    FindCollisions();
                }
                catch (Exception exception)
                {
                    RectangleWidthTextBox.BackColor = Color.Red;
                    _toolTip.SetToolTip(RectangleWidthTextBox, exception.Message);
                }
            }
        }

        private void RectanglesHeightTextBox_TextChanged(object sender, EventArgs e)
        {
            RectangleHeightTextBox.BackColor = Color.White;
            if (string.IsNullOrEmpty(RectangleHeightTextBox.Text) == false && RectanglesListBox.Items.Count != 0)
            {
                try
                {
                    RectangleHeightTextBox.BackColor = Color.White;
                    _currentRectangle.Height = Int32.Parse(RectangleHeightTextBox.Text);
                    _toolTip.SetToolTip(RectangleHeightTextBox, "");
                    UpdateRectanglesInfo(_currentRectangle);
                    ChangedRectanglePanel(_rectanglePanels[RectanglesListBox.SelectedIndex]);
                    FindCollisions();
                }

                catch (Exception exception)
                {
                    RectangleHeightTextBox.BackColor = Color.Red;
                    _toolTip.SetToolTip(RectangleHeightTextBox, exception.Message);
                }
            }
        }

        private void RectanglesXTextBox_TextChanged(object sender, EventArgs e)
        {
                
            RectangleXTextBox.BackColor = Color.White;
            if (string.IsNullOrEmpty(RectangleXTextBox.Text) == false && RectanglesListBox.Items.Count != 0)
            {
                try
                {
                    _currentRectangle.Centre.X = Int32.Parse(RectangleXTextBox.Text);
                    _toolTip.SetToolTip(RectangleXTextBox, "");
                    UpdateRectanglesInfo(_currentRectangle);
                    ChangedRectanglePanel(_rectanglePanels[RectanglesListBox.SelectedIndex]);
                    FindCollisions();
                }

                catch (Exception exception)
                {
                    RectangleXTextBox.BackColor = Color.Red;
                    _toolTip.SetToolTip(RectangleXTextBox, exception.Message);
                }
            }
        }

        private void RectanglesYTextBox_TextChanged(object sender, EventArgs e)
        {
            RectangleYTextBox.BackColor = Color.White;
            if (string.IsNullOrEmpty(RectangleYTextBox.Text) == false && RectanglesListBox.Items.Count != 0)
            {
                try
                {
                    _currentRectangle.Centre.Y = Int32.Parse(RectangleYTextBox.Text);
                    _toolTip.SetToolTip(RectangleYTextBox, "");
                    ChangedRectanglePanel(_rectanglePanels[RectanglesListBox.SelectedIndex]);
                    FindCollisions();
                    if (_currentRectangle.Centre.Y == Int32.Parse(RectangleYTextBox.Text))
                    {
                        UpdateRectanglesInfo(_currentRectangle);
                    }  
                }

                catch (Exception exception)
                {
                    _toolTip.SetToolTip(RectangleYTextBox, exception.Message);
                    RectangleYTextBox.BackColor = Color.Red;
                }
            }
        }

        private void MultiplyRectangleButton_Click(object sender, EventArgs e)
        {
            if(int.TryParse(MultiplyTextBox.Text, out _)) 
            {
                if(Convert.ToInt32(MultiplyTextBox.Text) >= 0)
                {
                    _currentRectangle.Width *= Convert.ToInt32(MultiplyTextBox.Text);
                    _currentRectangle.Height *= Convert.ToInt32(MultiplyTextBox.Text);
                    ChangedRectanglePanel(_rectanglePanels[RectanglesListBox.SelectedIndex]);
                    UpdateRectanglesInfo(_currentRectangle);
                    FindCollisions();
                }
                else
                {
                    MessageBox.Show("Число не должно быть меньше нуля!");
                }
            }
            else
            {
                MessageBox.Show("Введите число!");
            }
        }

        private void CompareRectanglesButton_Click(object sender, EventArgs e)
        {
            if(!(string.IsNullOrEmpty(FirstRectangleTextBox.Text) && string.IsNullOrEmpty(SecondRectangleTextBox.Text))) 
            {
                if (int.TryParse(FirstRectangleTextBox.Text, out _) && int.TryParse(SecondRectangleTextBox.Text, out _))
                {
                    Rectangle firstRectangle = _rectangles.Find(r => r.Id == Convert.ToInt32(FirstRectangleTextBox.Text));
                    Rectangle secondRectangle = _rectangles.Find(r => r.Id == Convert.ToInt32(SecondRectangleTextBox.Text));
                    if(firstRectangle != null && secondRectangle != null)
                    {
                        string isEqual = ((firstRectangle.Width == secondRectangle.Width) &&
                                                    (secondRectangle.Height == firstRectangle.Height)).ToString();
                        MessageBox.Show($"Rectangles is equal: {isEqual}");
                    }
                    else
                    {
                        MessageBox.Show("Прямоугольники должны существовать в списке!");
                    }
                }
                else
                {
                    MessageBox.Show("ID должны быть числовыми значениями!");
                }
            }
        }

        private void DrawStripes()
        {
            int width = CanvasPanel.Width;
            int height = CanvasPanel.Height;

            Panel verticalLine = new Panel();
            verticalLine.Location = new Point(width / 2, 0);
            verticalLine.Size = new Size(1, 10000);
            verticalLine.BackColor = Color.Black;
            CanvasPanel.Controls.Add(verticalLine);


            Panel horizontalLine = new Panel();
            horizontalLine.Location = new Point(0, height / 2);
            horizontalLine.Size = new Size(10000, 1);
            horizontalLine.BackColor = Color.Black;
            CanvasPanel.Controls.Add(horizontalLine);
        }
    }
}