using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace DataGridDemo
{
    public class Int2Image : IValueConverter
    {
        private static BitmapSource ok;
        private static BitmapSource delete;

        static Int2Image()
        {
            ok = new BitmapImage(new Uri("/Assets/ok.gif", UriKind.Relative));
            delete = new BitmapImage(new Uri("/Assets/delete.gif", UriKind.Relative));
        }

        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            int state = (int)value;
            switch (state)
            {
                case 1:
                    return ok;

                case 2:
                    return delete;

                default:
                    throw new ArgumentException("state");
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
