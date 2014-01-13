using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ReactiveUI;
using System.ComponentModel;
using System.Collections.ObjectModel;
using ReactiveUI.Legacy;

namespace WpfApplication1
{
    public class MainWindowDataObject : ReactiveObject
    {
        private int id;

        public int Id
        {
            get { return id; }
            set { this.RaiseAndSetIfChanged(ref id, value, "Id"); }
        }

        public override string ToString()
        {
            return id.ToString();
        }
    }

    public class MainWindowModel : ReactiveObject
    {
        private ObservableCollection<MainWindowDataObject> dataList = new ObservableCollection<MainWindowDataObject>();

        public ObservableCollection<MainWindowDataObject> DataList
        {
            get { return dataList; }
        }
    }
}
