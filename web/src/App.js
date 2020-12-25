import React, { useState } from 'react';
import {
    TextField,
    Drawer,
    CssBaseline,
    AppBar,
    Toolbar,
    Typography,
    IconButton,
    Tooltip,
} from '@material-ui/core';
import {
    makeStyles,
    createMuiTheme,
    ThemeProvider,
} from '@material-ui/core/styles';
import { blueGrey } from '@material-ui/core/colors';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import AddIcon from '@material-ui/icons/Add';
import applicationRedisSingleton from './services/ApplicationRedisSingleton';
import HomeRoute from './routes/Home';
import './styles/App.css';

const drawerWidth = 240;

const theme = createMuiTheme({
    palette: {
        primary: {
            main: blueGrey[900],
        },
    },
});

const useStyles = makeStyles((theme) => ({
    root: {
        display: 'flex',
    },
    appBar: {
        zIndex: theme.zIndex.drawer + 1,
    },
    drawer: {
        width: drawerWidth,
        flexShrink: 0,
    },
    drawerPaper: {
        width: drawerWidth,
    },
    drawerContainer: {
        overflow: 'auto',
        padding: theme.spacing(2),
    },
    content: {
        flexGrow: 1,
        padding: theme.spacing(3),
    },
    title: {
        flexGrow: 1,
    },
}));

function App() {
    const classes = useStyles();

    const [applicationName, setApplicationName] = useState('');
    const [redisHost, setRedisHost] = useState(
        localStorage.getItem('mlLogRedisHost') || '',
    );
    const [redisPort, setRedisPort] = useState(
        localStorage.getItem('mlLogRedisPort') || 0,
    );
    const [redisDatabaseIndex, setRedisDatabaseIndex] = useState(
        localStorage.getItem('mlLogRedisDatabaseIndex') || 0,
    );

    return (
        <ThemeProvider theme={theme}>
            <div className={classes.root}>
                <CssBaseline />
                <AppBar position="fixed" className={classes.appBar}>
                    <Toolbar>
                        <Typography variant="h6" className={classes.title}>
                            ml-log
                        </Typography>
                        <Tooltip title="Add plot">
                            <IconButton color="inherit">
                                <AddIcon />
                            </IconButton>
                        </Tooltip>
                    </Toolbar>
                </AppBar>
                <Drawer
                    className={classes.drawer}
                    variant="permanent"
                    classes={{
                        paper: classes.drawerPaper,
                    }}
                >
                    <Toolbar />
                    <div className={classes.drawerContainer}>
                        <TextField
                            id="outlined-basic"
                            label="Application Name"
                            variant="outlined"
                            value={applicationName}
                            onChange={(e) => {
                                setApplicationName(e.target.value);
                                applicationRedisSingleton.applicationName =
                                    e.target.value;
                            }}
                        />
                        <br />
                        <br />
                        <TextField
                            id="outlined-basic"
                            label="Redis Host"
                            variant="outlined"
                            value={redisHost}
                            onChange={(e) => {
                                setRedisHost(e.target.value);
                                applicationRedisSingleton.redisHost =
                                    e.target.value;
                                localStorage.setItem(
                                    'mlLogRedisHost',
                                    e.target.value,
                                );
                            }}
                        />
                        <br />
                        <br />
                        <TextField
                            id="outlined-basic"
                            label="Redis Port"
                            variant="outlined"
                            value={redisPort}
                            onChange={(e) => {
                                setRedisPort(e.target.value);
                                applicationRedisSingleton.redisPort =
                                    e.target.value;
                                localStorage.setItem(
                                    'mlLogRedisPort',
                                    e.target.value,
                                );
                            }}
                        />
                        <br />
                        <br />
                        <TextField
                            id="outlined-basic"
                            label="Redis Database Index"
                            variant="outlined"
                            value={redisDatabaseIndex}
                            onChange={(e) => {
                                setRedisDatabaseIndex(e.target.value);
                                applicationRedisSingleton.redisDatabaseIndex =
                                    e.target.value;
                                localStorage.setItem(
                                    'mlLogRedisDatabaseIndex',
                                    e.target.value,
                                );
                            }}
                        />
                    </div>
                </Drawer>
                <main className={classes.content}>
                    <Toolbar />
                    <Router>
                        <Switch>
                            <Route path="/" exact component={HomeRoute} />
                        </Switch>
                    </Router>
                </main>
            </div>
        </ThemeProvider>
    );
}

export default App;
