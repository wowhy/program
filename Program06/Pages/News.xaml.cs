using Program06.Common;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Program06
{
    /// <summary>
    /// News.xaml 的交互逻辑
    /// </summary>
    public partial class News : Page
    {
        public class ViewModel : BaseModel<Page>
        {
            public class Item : BaseModel
            {
                private string title;
                public string Title
                {
                    get { return title; }
                    set { SetValue(ref title, value, "Title"); }
                }

                private string content;
                public string Content
                {
                    get { return content; }
                    set { SetValue(ref content, value, "Content"); }
                }

                private string source;
                public string Source
                {
                    get { return source; }
                    set { SetValue(ref source, value, "Source"); }
                }

                private DateTime publishDate;
                public DateTime PublishDate
                {
                    get { return publishDate; }
                    set { SetValue(ref publishDate, value, "PublishDate"); }
                }
            }

            private BindingList<Item> allNews = new BindingList<Item>();
            public BindingList<Item> AllNews
            {
                get { return allNews; }
                set { SetValue(ref allNews, value, "AllNews"); }
            }

            public ViewModel(Page page)
                : base(page)
            {
            }
        }

        private ViewModel model;
        public ViewModel Model
        {
            get { return model; }
        }

        public News()
        {
            InitializeComponent();
            this.DataContext = model = new ViewModel(this);

            this.Loaded += News_Loaded;
        }

        private void News_Loaded(object sender, RoutedEventArgs e)
        {
            model.AllNews.Add(new ViewModel.Item() 
            {
                Title = "title1",
                Content = "Hello, World!",
                Source = "test",
                PublishDate = new DateTime(1900,1,1)
            });

            model.AllNews.Add(new ViewModel.Item()
            {
                Title = "title2",
                Content = "Hello, World!",
                Source = "test",
                PublishDate = new DateTime(2012, 12, 12)
            });

            model.AllNews.Add(new ViewModel.Item()
            {
                Title = "title3",
                Content = "Hello, World!",
                Source = "test",
                PublishDate = new DateTime(2011, 11, 11)
            });

            model.AllNews.Add(new ViewModel.Item()
            {
                Title = "title4",
                Content = "Hello, World!",
                Source = "test",
                PublishDate = new DateTime(2010, 10, 10)
            });
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            model.AllNews.Add(new ViewModel.Item()
            {
                Title = "title...",
                Content = "model.add",
                Source = "button",
                PublishDate = new DateTime(2010, 10, 10)
            });
        }
    }
}
