'use strict';
var isElevatedModule = null;
var tried = false;

module.exports = function() {
  if (!tried) {
    tried = true;
    try {
      isElevatedModule = require('./build/Release/is-elevated');
    } catch (err) {
      console.error(err);
    }
  }

  if (!isElevatedModule) {
    return false;
  }

  var r = false;
  try {
    r = isElevatedModule.isElevated();
  } catch (err) {
    console.error(err);
  }

  return r;
};
