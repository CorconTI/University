using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace lab7
{
    public class Accelerators : DbContext
    {
        public Accelerators()
        {

        }
        public DbSet<Group> Groups { get; set; }
        public DbSet<Device> Device { get; set; }

        

    }
    public class Device
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public double Energy { get; set; }
        public int Year { get; set; }
        public virtual Group Group { get; set; }
        public Device(string Name, double Energy, int Year)
        {
            this.Name = Name;
            this.Energy = Energy;
            this.Year = Year;
        }
        public Device()
        {
            Name = " ";
            Energy = 0;
            Year = 0;
        }

    }
    public class Group
    {
        public int Id { get; set; }

        public string Name { get; set; }
        public virtual List<Device> Device { get; set; }

        public Group()
        {
            Device = new List<Device>();
        }

    }
}
