using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DataGridDemo
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public class DataModel : INotifyPropertyChanged
        {
            private int id;
            public int Id
            {
                get { return id; }
                set { this.SetValue(ref id, value, "Id"); }
            }

            private string name;
            public string Name
            {
                get { return name; }
                set { this.SetValue(ref name, value, "Name"); }
            }

            private int age;
            public int Age
            {
                get { return age; }
                set { this.SetValue(ref age, value, "Age"); }
            }

            private string img;
            public string Img
            {
                get { return img; }
                set { this.SetValue(ref img, value, "Img"); }
            }

            private string email;
            public string Email
            {
                get { return email; }
                set { this.SetValue(ref email, value, "Email"); }
            }

            private string address;
            public string Address
            {
                get { return address; }
                set { this.SetValue(ref address, value, "Address"); }
            }

            private int state;
            public int State
            {
                get { return state; }
                set { this.SetValue(ref state, value, "State"); }
            }

            public event PropertyChangedEventHandler PropertyChanged;

            private void SetValue<T>(ref T p, T v, string name)
            {
                p = v;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        private ObservableCollection<DataModel> models = new ObservableCollection<DataModel>();
        private int lastIndex = 0;

        public MainWindow()
        {
            InitializeComponent();
            this.datagrid.ItemsSource = models;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.models.Add(new DataModel() 
            {
                Id = ++lastIndex,
                Age = 20,
                Address = "ABCDEFG",
                Email = "test@outlook.com",
                State = 1,
                Name = "测试",
                Img = "/Assets/ok.gif"                
            });
        }

        private void ImageButton_Click(object sender, RoutedEventArgs e)
        {
            var model = ((Button)sender).DataContext as DataModel;
            if (model == null)
                return;

            if (model.Img == "/Assets/ok.gif")
                model.Img = "/Assets/delete.gif";
            else
                model.Img = "/Assets/ok.gif";

            this.Title = string.Format("Id: {0}, Img: {1}", model.Id, model.Img);
        }

        private void ImageButton2_Click(object sender, RoutedEventArgs e)
        {
            var model = ((Button)sender).DataContext as DataModel;
            if (model == null)
                return;

            if (model.State == 1)
                model.State = 2;
            else
                model.State = 1;

            this.Title = string.Format("Id: {0}, State: {1}", model.Id, model.State);
        }
    }
}
