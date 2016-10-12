namespace GraphImageCreator
{
    partial class GraphImage
    {


        System.Single titlefontsize = new System.Single();
        System.Single xyfontsize = new System.Single();
        System.Single xycaptionsize = new System.Single();
        System.Single legendsize = new System.Single();

        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        private void setupChart(System.Windows.Forms.DataVisualization.Charting.Chart chart, int id)
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Title title = new System.Windows.Forms.DataVisualization.Charting.Title();

            string chartName = "Chart" + id.ToString();
            string chartAreaName = "ChartArea";
            string legendName = "Legend";
            string titleName = "Title";

            chartArea.Name = chartAreaName;
            chart.ChartAreas.Add(chartArea);
            chart.Dock = System.Windows.Forms.DockStyle.Fill;
            legend.Name = legendName;
            legend.Font = new System.Drawing.Font("Trebuchet MS", legendsize);
            chart.Legends.Add(legend);
            chart.Location = new System.Drawing.Point(3, 3);
            chart.Name = chartName;
            chart.Size = new System.Drawing.Size(590, 266);
            chart.TabIndex = 0;
            chart.Text = chartName;
            title.Name = titleName;
            title.Font = new System.Drawing.Font("Trebuchet MS", titlefontsize);
            chart.Titles.Add(title);
        }

        private void setupBarChart(System.Windows.Forms.DataVisualization.Charting.Chart chart, int id)
        {
            setupChart(chart, id);
            chart.ChartAreas[0].AxisX.IsLabelAutoFit = true;
            chart.ChartAreas[0].AxisX.LabelAutoFitStyle = System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.LabelsAngleStep30;
            chart.ChartAreas[0].AxisX.LabelStyle.Enabled = true;
        }

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            // setting font size
            titlefontsize = 18F;
            xyfontsize = 18F;
            xycaptionsize = 18F;
            legendsize = 16F;

            this.CrunchButton = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.filesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectFilesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.chart2 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.chart3 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.chart4 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.chart5 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart5)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.SuspendLayout();
            // 
            // chart1
            // 
            setupChart(chart1, 1);
            this.chart1.Titles[0].Text = "Mean Distance per Generation";
            this.chart1.ChartAreas[0].AxisX.Title = "generation";
            this.chart1.ChartAreas[0].AxisY.Title = "distance";
            this.chart1.ChartAreas[0].AxisX.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart1.ChartAreas[0].AxisY.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart1.ChartAreas[0].AxisX.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            this.chart1.ChartAreas[0].AxisY.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            // 
            // chart2
            // 
            setupBarChart(chart2, 2);
            this.chart2.Titles[0].Text = "Mean Final Distance";
            this.chart2.ChartAreas[0].AxisY.Title = "distance";
            this.chart2.ChartAreas[0].AxisX.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart2.ChartAreas[0].AxisY.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart2.ChartAreas[0].AxisX.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            this.chart2.ChartAreas[0].AxisY.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            // 
            // chart3
            // 
            setupBarChart(chart3, 3);
            this.chart3.Titles[0].Text = "Mean Count of Generations";
            this.chart3.ChartAreas[0].AxisY.Title = "generations";
            this.chart3.ChartAreas[0].AxisX.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart3.ChartAreas[0].AxisY.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart3.ChartAreas[0].AxisX.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            this.chart3.ChartAreas[0].AxisY.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            // 
            // chart4
            // 
            setupBarChart(chart4, 4);
            this.chart4.Titles[0].Text = "Mean Time per Generation";
            this.chart4.ChartAreas[0].AxisY.Title = "seconds";
            this.chart4.ChartAreas[0].AxisX.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart4.ChartAreas[0].AxisY.LabelStyle.Font = new System.Drawing.Font("Trebuchet MS", xyfontsize);
            this.chart4.ChartAreas[0].AxisX.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            this.chart4.ChartAreas[0].AxisY.TitleFont = new System.Drawing.Font("Trebuchet MS", xycaptionsize);
            // 
            // chart5
            // 
            setupBarChart(chart5, 5);
            this.chart5.Titles[0].Text = "Totel Time";
            this.chart5.ChartAreas[0].AxisY.Title = "something goes here";
            // 
            // CrunchButton
            // 
            this.CrunchButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.CrunchButton.Location = new System.Drawing.Point(538, 331);
            this.CrunchButton.Name = "CrunchButton";
            this.CrunchButton.Size = new System.Drawing.Size(78, 23);
            this.CrunchButton.TabIndex = 1;
            this.CrunchButton.Text = "Crunch Data";
            this.CrunchButton.UseVisualStyleBackColor = true;
            this.CrunchButton.Click += new System.EventHandler(this.CrunchButton_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.filesToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(628, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // filesToolStripMenuItem
            // 
            this.filesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectFilesToolStripMenuItem,
            this.saveAsImageToolStripMenuItem});
            this.filesToolStripMenuItem.Name = "filesToolStripMenuItem";
            this.filesToolStripMenuItem.Size = new System.Drawing.Size(42, 20);
            this.filesToolStripMenuItem.Text = "Files";
            // 
            // selectFilesToolStripMenuItem
            // 
            this.selectFilesToolStripMenuItem.Name = "selectFilesToolStripMenuItem";
            this.selectFilesToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.selectFilesToolStripMenuItem.Text = "Select Files ...";
            this.selectFilesToolStripMenuItem.Click += new System.EventHandler(this.selectFilesToolStripMenuItem_Click);
            // 
            // saveAsImageToolStripMenuItem
            // 
            this.saveAsImageToolStripMenuItem.Name = "saveAsImageToolStripMenuItem";
            this.saveAsImageToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.saveAsImageToolStripMenuItem.Text = "Save As Image ...";
            this.saveAsImageToolStripMenuItem.Click += new System.EventHandler(this.saveAsImageToolStripMenuItem_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.Location = new System.Drawing.Point(12, 27);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(604, 298);
            this.tabControl1.TabIndex = 3;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.chart1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(596, 272);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Dist Per Gen";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.chart2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(596, 272);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Final Dist";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.chart3);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(596, 272);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Gen Count";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.chart4);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(596, 272);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Time Per Gen";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.chart5);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Size = new System.Drawing.Size(596, 272);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "Total Time";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // GraphImage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(628, 366);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.CrunchButton);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "GraphImage";
            this.Text = "TSP Graphs";
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chart5)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        

        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart2;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart3;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart4;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart5;

        private System.Windows.Forms.Button CrunchButton;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem filesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectFilesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsImageToolStripMenuItem;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.TabPage tabPage5;
    }
}

