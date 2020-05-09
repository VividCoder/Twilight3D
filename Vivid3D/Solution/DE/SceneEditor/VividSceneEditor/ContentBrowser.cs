using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.CompilerServices;
using VividSceneEditor.Browser;

namespace VividSceneEditor
{
    public partial class ContentBrowser : WeifenLuo.WinFormsUI.Docking.DockContent
    {

        public static string ContentPath = "";
        public static ContentBrowser CB;

        public static Browser.BrowserContent ContentOver;
        public static Browser.BrowserContent ContentActive;
        public static Browser.BrowserContent ContentDrag;

        public ContentBrowser()
        {
            InitializeComponent();
            CB = this;
           
        }

        public void SetPath(string path)
        {


            ContentPath = path;
            ScanPath();

        }

        public List<Browser.BrowserContent> Contents = new List<Browser.BrowserContent>();

        public void ScanPath()
        {

            Contents.Clear();

            var dinfo = new DirectoryInfo(ContentPath);

            int bx = 10;
            int by = 10;

            var folder_image = new Bitmap("edit\\folder.png");
            var file_image = new Bitmap("edit\\file.png");


            foreach(var info in dinfo.GetDirectories())
            {

                var cf = new Browser.ContentFolder();

                cf.Img = folder_image;

                cf.RealPath = info.FullName;
                cf.LocalPath = info.Name;

                cf.CX = bx;
                cf.CY = by;

                bx = bx + 112;
                if (bx > Size.Width - 128)
                {
                    bx = 5;
                    by = by + 128;
                }
                Contents.Add(cf);

            }

            foreach(var info in dinfo.GetFiles())
            {


                var cf = new Browser.ContentFile();

                cf.Img = file_image;

                cf.RealPath = info.FullName;
                cf.LocalPath = info.Name;

                cf.CX = bx;
                cf.CY = by;

                bx = bx + 112;
                if(bx>Size.Width-128)
                {
                    bx = 5;
                    by = by + 128;
                }
                Contents.Add(cf);

            }

            Invalidate();

        }

        private void ContentBrowser_Paint(object sender, PaintEventArgs e)
        {

            foreach(var content in Contents)
            {

                if(content == ContentOver)
                {

                    e.Graphics.DrawRectangle(Pens.LightBlue, new Rectangle(content.CX-6, content.CY-4, 66, 72));

                }else if(content == ContentActive)
                {

                    e.Graphics.DrawRectangle(Pens.White, new Rectangle(content.CX - 6, content.CY - 4, 66, 72));

                }
                e.Graphics.DrawImage(content.Img,new Rectangle(content.CX,content.CY,54,54));
                e.Graphics.DrawString(content.LocalPath, SystemFonts.CaptionFont, Brushes.LightGray, new PointF(content.CX, content.CY+50));
                if(content == ContentOver)
                {
                    e.Graphics.DrawString(content.LocalPath, SystemFonts.CaptionFont, Brushes.LightGray, new PointF(content.CX, content.CY + 16));
                }
            }

        }

        private void ContentBrowser_MouseMove(object sender, MouseEventArgs e)
        {

            int mx = e.X;
            int my = e.Y;
            ContentOver = null;

            if (ContentDrag != null)
            {


                int cx = e.X - dx;
                int cy = e.Y - dy;

                ContentDrag.CX += cx;
                ContentDrag.CY += cy;

                dx = e.X;
                dy = e.Y;

                Invalidate();
                return;

            }

            foreach(var content in Contents)
            {

                if(mx>content.CX && mx<content.CX+54)
                {
                    if (my > content.CY && my < content.CY + 54)
                    {

                        ContentOver = content;
                        Invalidate();

                    }

                }

            }
            Invalidate();
        }



        private void ContentBrowser_MouseDown(object sender, MouseEventArgs e)
        {
            int mx = e.X;
            int my = e.Y;
            ContentActive = null;
            ContentOver = null;

            if (e.Button == MouseButtons.XButton1)
            {
                
            }

            foreach (var content in Contents)
            {

                if (mx > content.CX && mx < content.CX + 54)
                {
                    if (my > content.CY && my < content.CY + 54)
                    {

                        ContentActive = content;
                        ContentDrag = content;
                        dx = e.X;
                        dy = e.Y;
                       
                    }

                }

            }
            Invalidate();

        }

        int dx, dy;

        private void ContentBrowser_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (ContentActive != null)
            {

                if (ContentActive is ContentFolder)
                {
                    SetPath(ContentActive.RealPath)
                        ;
                }
            }
        }

        private void ContentBrowser_MouseUp(object sender, MouseEventArgs e)
        {
            ContentDrag = null;
            Invalidate();
        }
    }
}
