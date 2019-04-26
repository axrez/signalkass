import React from 'react';
import PropTypes from 'prop-types';
import { distanceInWords } from 'date-fns';

import { MeasureEntry } from './MeasureEntry';

const DataTabel = ({ data, click }) => {
  const list = data.map((d, i) => (
    <MeasureEntry key={i} onClick={click} id={d}>
      {distanceInWords(Date.now(), d)} ago
    </MeasureEntry>
  ));
  return (
    <>
      <h4>table someday</h4>
      <ul>{list}</ul>
    </>
  );
};

DataTabel.propTypes = {
  data: PropTypes.array.isRequired,
  click: PropTypes.func.isRequired,
};

export default DataTabel;
