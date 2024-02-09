using System;
using System.Collections.Generic;
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
using System.Data.Entity;

namespace lab7
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public Group EdittedGroup { get; set; }
        public Group groupS { get; set; } //хранение выбранной группы
        public MainWindow()
        {
            InitializeComponent();
            Accelerators context = new Accelerators();
            context.Groups.Load();
            GroupGrid.ItemsSource = context.Groups.Local.ToBindingList();
            Group group = new Group() { Name = "Синхротроны" };
            if (!context.Groups.Any(x => x.Name == group.Name))
            {
                group.Device.AddRange(new List<Device>()
                    { new Device("Сибирь", 3, 1970), new Device("ВЭПП-4", 2,1980)});
                context.Groups.Add(group);
                context.SaveChanges();
            }
            

        }
        private void MainWindow_OnLoaded(Object sender, RoutedEventArgs e)
        {
           
            
        }

        private void AddGroup(object sender, RoutedEventArgs e)
        {
          
        }

        private void GroupSelected(object sender, MouseButtonEventArgs e)
        {
            
            Accelerators context = new Accelerators();  //контекст для загрузки всех устройств
            context.Device.Load();  //загрузка всех устройств из базы данных
            groupS = (Group)GroupGrid.SelectedItem; //"вытаскивание" из окна выбранной группы
            foreach (Device item in context.Device)//проход по всем устройствам в контексте
            {
                if (item.Group.Name != groupS.Name) //проверка на несовпадение с выбранной группы
                    context.Device.Remove(item);    //удаление лишних устройств
                    
            }
            AccGrid.ItemsSource = context.Device.Local.ToBindingList(); //привязка к обработанной коллекции выбранных устройств
        }

        private void RowEditEndingGroup(object sender, DataGridRowEditEndingEventArgs e)
        {
            
        }

        private void BeginningEditGroup(object sender, DataGridBeginningEditEventArgs e)
        {
            
            Accelerators context = new Accelerators();  //контекст для загрузки всех устройств
            context.Device.Load();  //загрузка всех устройств из базы данных
            groupS = (Group)GroupGrid.SelectedItem; //"вытаскивание" из окна выбранной группы
        }
    }
}

