using System.Windows;

namespace WinZipIde;

public static class Program
{
    [STAThread]
    public static void Main()
    {
        var app = new Application();
        app.Run(new MainWindow());
    }
}

public sealed class MainWindow : Window
{
    public MainWindow()
    {
        Title = "WinZip Electron IDE";
        Width = 1400;
        Height = 900;

        Content = new System.Windows.Controls.TextBlock
        {
            Text = "WinZip Electron IDE",
            FontSize = 28,
            Margin = new Thickness(32)
        };
    }
}
