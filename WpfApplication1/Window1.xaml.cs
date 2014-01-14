using ReactiveUI;
using ReactiveUI.Legacy;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Reactive;
using System.Reactive.Linq;
using System.Threading;
using System.Windows;

namespace WpfApplication1
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class Window1 : Window
    {
        public class ListObject : ReactiveObject, 
            IComparable<ListObject>
        {
            private int _value;

            public int Value
            {
                get { return _value; }
                set { this.RaiseAndSetIfChanged(ref this._value, value); }
            }

            public ListObject()
            { }

            public ListObject(int value)
            {
                this._value = value;
            }

            public static implicit operator ListObject(int value)
            {
                return new ListObject(value);
            }

            public int CompareTo(ListObject other)
            {
                return this._value.CompareTo(other._value);
            }
        }

        public class _ViewModel : ReactiveObject
        {
            private bool asc = false;

            private string title;

            public string Title
            {
                get { return title; }
                set { this.RaiseAndSetIfChanged(ref title, value); }
            }

            private double progressBarWidth;

            public double ProgressBarWidth
            {
                get { return progressBarWidth; }
                set { this.RaiseAndSetIfChanged(ref progressBarWidth, value); }
            }

            private bool canExecute = true;

            public bool CanExecute
            {
                get { return canExecute; }
                set { this.RaiseAndSetIfChanged(ref canExecute, value); }
            }

            private ReactiveList<ListObject> dataList;

            public ReactiveList<ListObject> DataList
            {
                get { return dataList; }
            }

            public ReactiveAsyncCommand SortCommand { get; private set; }

            public ReactiveAsyncCommand RandomCommand { get; private set; }

            public _ViewModel()
            {
                this.dataList = new ReactiveList<ListObject>();

                SortCommand = new ReactiveAsyncCommand();
                SortCommand.RegisterAsyncAction(obj=> Command(obj, this.BubbleSortDataList));

                RandomCommand = new ReactiveAsyncCommand();
                RandomCommand.RegisterAsyncAction(obj => Command(obj, this.RandomDataList));

                this.RandomDataList();
            }

            private void Command(object obj, Action action)
            {
                this.Title = "#" + Thread.CurrentThread.ManagedThreadId.ToString();
                this.CanExecute = false;
                action();
                this.CanExecute = true;
            }

            private void BubbleSortDataList()
            {
                var comparer = asc ?
                    new Func<int, int, bool>((x, y) => { return x < y; }) :
                    new Func<int, int, bool>((x, y) => { return x > y; });

                asc = !asc;

                var count = dataList.Count;
                for (var i = 0; i < count; ++i)
                {
                    for (var j = 0; j < count - i - 1; ++j)
                    {
                        if (comparer(dataList[j].Value, dataList[j + 1].Value))
                        {
                            var tmp = dataList[j + 1].Value;
                            dataList[j + 1].Value = dataList[j].Value;
                            dataList[j].Value = tmp;

                            Thread.Sleep(41);
                        }
                    }
                }
            }

            private void RandomDataList()
            {
                var action = dataList.Count == 0 ?
                    new Action<int, int>((x, i) => dataList.Add(x)) :
                    new Action<int, int>((x, i) => dataList[i].Value = x);

                var rand = new Random((int)DateTime.Now.Ticks);
                int count = 25;
                for (var i = 0; i < count; ++i)
                {
                    action(rand.Next(0, 100) + 1, i);
                }
            }
        }

        public _ViewModel ViewModel { get; protected set; }

        public Window1()
        {
            this.ViewModel = new _ViewModel();
            InitializeComponent();

            this.Loaded += (sender, e) =>
            {
                this.ViewModel.Title = "#" + Thread.CurrentThread.ManagedThreadId.ToString();
            };

            this.SizeChanged += (sender, e) => 
            {
                this.ViewModel.ProgressBarWidth = this.ActualWidth - 30;
            };
        }
    }
}
