import React, { useEffect } from 'react';
import Plot from 'react-plotly.js';
import config from '../config.json';

async function getKeys() {
    // let promise = fetch(`${config.endpoint}/`);
    // console.log(config);
}

function HomeRoute() {
    useEffect(() => {
        getKeys();
    }, []);

    return (
        <div>
            <Plot
                data={[
                    {
                        x: [1, 2, 3],
                        y: [2, 6, 3],
                        type: 'scatter',
                        mode: 'lines+markers',
                    },
                    {
                        x: [1, 2, 3] * 2,
                        y: [2, 6, 3],
                        type: 'scatter',
                        mode: 'lines+markers',
                    },
                ]}
                layout={{ title: 'A Fancy Plot' }}
            />
        </div>
    );
}

export default HomeRoute;
