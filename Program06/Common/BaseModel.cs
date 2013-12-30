using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Program06.Common
{
    public class BaseModel<T> : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public void SetValue<TProperty>(ref TProperty propery, TProperty value, string name)
        {
            propery = value;
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        private T control;
        public T Control
        {
            get { return control; }
            set { control = value; }
        }

        public BaseModel()
        {
        }

        public BaseModel(T obj)
        {
            this.control = obj;
        }
    }

    public class BaseModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public void SetValue<TProperty>(ref TProperty propery, TProperty value, string name)
        {
            propery = value;
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        private object control;
        public object Control
        {
            get { return control; }
        }

        public BaseModel()
        {
        }

        public BaseModel(object obj)
        {
            this.control = obj;
        }
    }
}
