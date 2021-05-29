const path = require('path');
const webpack = require('webpack');

const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
  mode: 'development',
  entry: {
    index: './src/hebrew.bs.js'
  },

  plugins: [
    new HtmlWebpackPlugin({
      title: 'Hebrew',
      template: './src/index.html'
    })
  ],
  output: {
    filename: '[name].bundle.js',
    path: path.resolve(__dirname, 'dist'),
    clean: true
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: [ 'style-loader', 'css-loader' ]
      }
    ]
  },
  devServer: {
    compress: true,
    port: process.env.PORT || 8888,
    historyApiFallback: true,
    stats: 'minimal'
  }
};
