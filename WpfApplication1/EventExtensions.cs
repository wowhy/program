using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Reactive;
using System.Windows.Controls.Primitives;
using System.Windows.Controls;
using System.Reactive.Linq;

namespace WpfApplication1
{
    public static class EventExtensions
    {
        public static IObservable<EventPattern<RoutedEventArgs>> ClickAsObservable(
            this ButtonBase This)
        {
            return Observable.FromEventPattern<RoutedEventHandler, RoutedEventArgs>(
                                k => k.Invoke,
                                k => This.Click += k,
                                k => This.Click -= k)
                             .Select(k => k);
        }

        public static IDisposable SubscribeDispatcher<T>(
            this IObservable<T> This,
            Window window,
            Action<T> onNext)
        {
            return This.Subscribe<T>(k =>
            {
                window.Dispatcher.Invoke(() =>
                {
                    onNext(k);
                });
            });
        }
    }
}
