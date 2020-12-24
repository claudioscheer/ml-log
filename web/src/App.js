import React from 'react';
import {
    makeStyles,
    createMuiTheme,
    ThemeProvider,
} from '@material-ui/core/styles';
import Drawer from '@material-ui/core/Drawer';
import CssBaseline from '@material-ui/core/CssBaseline';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import List from '@material-ui/core/List';
import Typography from '@material-ui/core/Typography';
import Divider from '@material-ui/core/Divider';
import ListItem from '@material-ui/core/ListItem';
import ListItemIcon from '@material-ui/core/ListItemIcon';
import ListItemText from '@material-ui/core/ListItemText';
import InboxIcon from '@material-ui/icons/MoveToInbox';
import MailIcon from '@material-ui/icons/Mail';
import { blueGrey } from '@material-ui/core/colors';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
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
    },
    content: {
        flexGrow: 1,
        padding: theme.spacing(3),
    },
}));

function App() {
    const classes = useStyles();

    return (
        <ThemeProvider theme={theme}>
            <div className={classes.root}>
                <CssBaseline />
                <AppBar position="fixed" className={classes.appBar}>
                    <Toolbar>
                        <Typography variant="h6" noWrap>
                            ml-log
                        </Typography>
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
                        <List>
                            {['Inbox', 'Starred', 'Send email', 'Drafts'].map(
                                (text, index) => (
                                    <ListItem button key={text}>
                                        <ListItemIcon>
                                            {index % 2 === 0 ? (
                                                <InboxIcon />
                                            ) : (
                                                <MailIcon />
                                            )}
                                        </ListItemIcon>
                                        <ListItemText primary={text} />
                                    </ListItem>
                                ),
                            )}
                        </List>
                        <Divider />
                        <List>
                            {['All mail', 'Trash', 'Spam'].map(
                                (text, index) => (
                                    <ListItem button key={text}>
                                        <ListItemIcon>
                                            {index % 2 === 0 ? (
                                                <InboxIcon />
                                            ) : (
                                                <MailIcon />
                                            )}
                                        </ListItemIcon>
                                        <ListItemText primary={text} />
                                    </ListItem>
                                ),
                            )}
                        </List>
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
