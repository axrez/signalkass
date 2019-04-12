const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const MeasureMapSchema = new Schema ({
  created: {
    type: Date
  },
  index: {
    type: Number
  }
})

module.exports = MeasureMap = mongoose.model('measureMap', MeasureMapSchema);

