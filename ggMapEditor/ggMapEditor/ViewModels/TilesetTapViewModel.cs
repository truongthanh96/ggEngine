﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using ggMapEditor.Commands;

namespace ggMapEditor.ViewModels
{
    class TilesetTapViewModel : Main.AnchorTabViewModel
    {
        private Models.Tileset tileset;
        private ObservableCollection<Views.Controls.Tile> ctrlTiles;

        #region Properties
        public string TilesetName { get; set; }
        public ObservableCollection<Views.Controls.Tile> CtrlTiles
        {
            get { return ctrlTiles; }
            private set
            {
                ctrlTiles = value;
                RaisePropertyChanged("CtrlTiles");
            }
        }
        #endregion

        public TilesetTapViewModel(Models.Tileset tset)
        {
            tileset = tset;
            CtrlTiles = new ObservableCollection<Views.Controls.Tile>();
            SplitCells();
        }

        #region Other functions
        private void SplitCells()
        {
            var tiles = new ObservableCollection<Views.Controls.Tile>();
            BitmapImage source = new BitmapImage(tileset.imageUri);

            foreach (var t in tileset.tileList)
            {
                Views.Controls.Tile tile = new Views.Controls.Tile();
                CroppedBitmap croppedBitmap = new CroppedBitmap(source, new Int32Rect(t.x, t.y, tileset.tileWidth, tileset.tileHeight));
                tile.TileSource = croppedBitmap;
                tile.TileWidth = tileset.tileWidth;
                tile.TileHeight = tileset.tileHeight;
                tile.ImgId = t.id;
                tile.TilesetKey = tileset.id;
                tiles.Add(tile);
            }
            CtrlTiles = tiles;
        }
        #endregion

        #region Commands
        //public RelayCommand selectionChangedCommand;
        //public RelayCommand SelectionChangedCommand
        //{
        //    get
        //    {
        //        if (selectionChangedCommand == null)
        //            return selectionChangedCommand
        //                = new RelayCommand(param => ExecuteSelectionChanged((SelectionChangedEventArgs)param));
        //        return selectionChangedCommand;
        //    }
        //    set { selectionChangedCommand = value; }
        //}

        //private void ExecuteSelectionChanged(SelectionChangedEventArgs param)
        //{
        //    MessageBox.Show("abc");
        //}
        #endregion
    }
}
