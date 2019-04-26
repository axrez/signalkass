import React from 'react';
import PropTypes from 'prop-types';

import MeasureEntry from './MeasureEntry';

const DataTabel = ({ data }) => {
  const list = data.map((d, i) => <MeasureEntry key={i}>{d}</MeasureEntry>);
  return (
    <>
      <h4>table someday</h4>
      <ul>{list}</ul>
    </>
  );
};

DataTabel.propTypes = {
  data: PropTypes.array.isRequired,
};

export default DataTabel;
